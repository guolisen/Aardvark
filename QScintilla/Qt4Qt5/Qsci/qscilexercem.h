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
        //! The default.
        Default = 0,

        //! An error.
        Error = 1,

        //! A comment.
        Comment = 2,

        //! A number.
        Number = 3,

        //! A keyword.
        Keyword = 4,

        //! A double-quoted string.
        DoubleQuotedString = 5,

        //! A single-quoted string.
        SingleQuotedString = 6,

        //! An operator.
        Operator = 7,

        //! An identifier
        Identifier = 8,

        //! A scalar.
        Scalar = 9,

        //! Parameter expansion.
        ParameterExpansion = 10,

        //! Backticks.
        Backticks = 11,

        //! A here document delimiter.
        HereDocumentDelimiter = 12,

        //! A single quoted here document.
        SingleQuotedHereDocument = 13
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
