// This defines the interface to the QsciLexerCustom class.
//
// Copyright (c) 2018 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of QScintilla.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#ifndef QSCILEXERCEM_H
#define QSCILEXERCEM_H

#include <Qsci/qsciglobal.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercustom.h>

class QsciScintilla;
class QsciStyle;

class QsciLexerCem : public QsciLexerCustom
{
    Q_OBJECT

public:
    enum {
        DEFAULT = 0,
        TIME = 1,
        MODULENAME = 2,
        LOGLEVEL = 3,
        THREADID = 4,
        FUNCTION = 5,
        FILENAME = 6,
        FILENAME_LINENUM = 7,
        LOG = 8,
    };

    QsciLexerCem(QObject *parent = nullptr);
    virtual ~QsciLexerCem();

    const char *lexer() const;
    virtual const char *language() const;
    virtual QString description(int style) const;
    virtual QColor defaultColor(int style) const;
    virtual void styleText(int start, int end);

private:
    QsciLexerCem(const QsciLexerCem &);
    QsciLexerCem &operator=(const QsciLexerCem &);

    int cur_;
};

#endif
