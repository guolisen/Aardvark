// This module implements the QsciLexerCem class.
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


#include "Qsci/qscilexercem.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qsciscintillabase.h"
#include "Qsci/qscistyle.h"
#include <QDebug>

// The ctor.
QsciLexerCem::QsciLexerCem(QObject *parent)
    : QsciLexerCustom(parent)
{
}

// The dtor.
QsciLexerCem::~QsciLexerCem()
{
}

const char *QsciLexerCem::language() const
{
    return "Cem";
}

const char *QsciLexerCem::lexer() const
{
    return "cem";
}

QString QsciLexerCem::description(int style) const
{
    switch (style)
    {
    case Default:
        return "Default";

    case Error:
    case Backticks:
        return "Error";

    case Comment:
        return "Comment";

    case Number:
        return "Number";

    case Keyword:
        return "Keyword";

    case DoubleQuotedString:
    case SingleQuotedString:
    case SingleQuotedHereDocument:
        return "DoubleQuotedString";

    case Operator:
    case Identifier:
    case Scalar:
    case ParameterExpansion:
    case HereDocumentDelimiter:
        return "Operator";
    }

    return "";
}

QColor QsciLexerCem::defaultColor(int style) const
{
    switch (style)
    {
    case Default:
        return QColor(0x80,0x80,0x80);

    case Error:
    case Backticks:
        return QColor(0xff,0xff,0x00);

    case Comment:
        return QColor(0x00,0x7f,0x00);

    case Number:
        return QColor(0x00,0x7f,0x7f);

    case Keyword:
        return QColor(0x00,0x00,0x7f);

    case DoubleQuotedString:
    case SingleQuotedString:
    case SingleQuotedHereDocument:
        return QColor(0x7f,0x00,0x7f);

    case Operator:
    case Identifier:
    case Scalar:
    case ParameterExpansion:
    case HereDocumentDelimiter:
        return QColor(0x00,0x00,0x00);
    }

    return QsciLexer::defaultColor(style);
}

void QsciLexerCem::styleText(int start, int end)
{
#if 0
    int state = 0;
    int pos = 0;
    int index = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION, start);

    if (index > 0)
    {
        pos = editor()->SendScintilla(QsciScintillaBase::SCI_GETLINEENDPOSITION, index - 1);
        state = editor()->SendScintilla(QsciScintillaBase::SCI_GETSTYLEAT, pos);
    }
    else
    {
        state = Default;
        startStyling(start, 0x1f);
    }

    QString source = editor()->text();
    QStringList list = source.split("\n");
    QString line;
    Q_FOREACH(line, list)
    {
        int length = line.length();
        if (line[0] == '#')
        {
            state = Comment;
        }
        else
        {
            state = Default;
        }
        setStyling(length, state);
        index += 1;
    }
#if 0
    for line in source.splitlines(True):
        length = len(line)
        if line.startswith(b'#'):
            state = self.Comment
        else:
            # the following will style lines like "x = 0"
            pos = line.find(b'=')
            if pos > 0:
                set_style(pos, self.Key)
                set_style(1, self.Assignment)
                length = length - pos - 1
                state = self.Value
            else:
                state = self.Default
        set_style(length, state)
        # folding implementation goes here
        index += 1

  #endif
  #endif
    if (editor())
    {
        QString target = editor()->text(start, end);
        qDebug() << "!!!!!!!!!!!!!!!!!!Test(" << start << ":" << end << "): " << target;
        //setStyling(20, 3);
        //cur_ += 20;
    }
}


