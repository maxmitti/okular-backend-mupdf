/***************************************************************************
 *   Copyright (C) 2008 by Pino Toscano <pino@kde.org>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef QMUPDF_DOCUMENT_HPP
#define QMUPDF_DOCUMENT_HPP

extern "C" {
#include <mupdf/fitz.h>
}

#include <okular/core/document.h>

#include <QString>
#include <QVector>

namespace QMuPDF {

class Page;
class Outline;

class Document {
public:
    enum PageMode {
        UseNone,
        UseOutlines,
        UseThumbs,
        FullScreen,
        UseOC,
        UseAttachments
    };
    Document();
    ~Document();
    bool load(const QString &fileName);
    void close();
    bool isLocked() const;
    bool unlock(const QByteArray &password);
    int pageCount() const;
    Page page(int page) const;
    QList<QByteArray> infoKeys() const;
    QString infoKey(const QByteArray &key) const;
    Outline *outline() const;
    float pdfVersion() const;
    PageMode pageMode() const;
    fz_context *ctx() const;
    fz_document *doc() const;
private:
    Q_DISABLE_COPY(Document)
    struct Data;
    Data *d;
};

class LinkDest;

class Outline {
public:
    Outline(const fz_outline *fz);
    Outline(): m_open(false) { }
    ~Outline();
    QString title() const { return m_title; }
    bool isOpen() const { return m_open; }
    QVector<Outline*> children() const { return m_children; }
    void appendChild(Outline *child) { m_children.push_back(child); }
    const std::string &link() const { return m_link; }
private:
    Q_DISABLE_COPY(Outline)
    QString m_title;
    QVector<Outline*> m_children;
    bool m_open : 1;
    std::string m_link;
};

}

#endif
