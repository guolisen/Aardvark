#include <QDebug>
#include "configmgr.h"
#include <QSci/qsciscintilla.h>
#include <QSci/qscilexercem.h>

namespace core {

const int MarginFold = 3;
const int MarginLineNum = 2;
const int MarginMark = 1;

//ConfigMgr::ConfigMgr(QObject *parent):
    //settings_("./Config.ini", QSettings::IniFormat)

ConfigMgr::ConfigMgr(QObject *parent):
    IConfigMgr(parent)
{

}

int ConfigMgr::getMarginWidthByLineNum(int lineNum)
{
    int count = 1;
    while(true)
    {
        lineNum /= 10;
        if(!lineNum)
            return count * 15;
        ++count;
    }
}

void ConfigMgr::configSciObject(QsciScintillaPtr sciPtr)
{
    sciPtr->markerDefine((QsciScintilla::MarkerSymbol)QsciScintilla::SC_MARK_ARROW, MarginMark);
    sciPtr->setMarginBackgroundColor(MarginMark, QColor(100, 0, 0));
    //sciPtr->setMarginsForegroundColor(QColor(0, 200, 0));
    sciPtr->setMarkerForegroundColor(QColor(0, 200, 0), MarginMark);
    sciPtr->setMarkerBackgroundColor(QColor(100, 100, 100), MarginMark);
    sciPtr->setMarginOptions(QsciScintilla::SC_MARGINOPTION_SUBLINESELECT);
    sciPtr->setMarginSensitivity(3, true);
    sciPtr->setMarginSensitivity(2, true);
    sciPtr->setMarginSensitivity(1, true);
sciPtr->setMarginSensitivity(0, true);
    sciPtr->setMarginMarkerMask(MarginMark, 0xFF);
    sciPtr->setMarginType(MarginMark, QsciScintilla::SymbolMargin);
    sciPtr->setMarginWidth(MarginMark, 20);

    sciPtr->setMarginType(MarginLineNum, QsciScintilla::NumberMargin);
    sciPtr->setMarginWidth(MarginLineNum, getMarginWidthByLineNum(sciPtr->lines()));

    sciPtr->setMarginType(MarginFold, QsciScintilla::SymbolMargin);
    sciPtr->setMarginMarkerMask(MarginFold, QsciScintilla::SC_MASK_FOLDERS);
    sciPtr->setFolding(QsciScintilla::BoxedTreeFoldStyle, MarginFold);

    sciPtr->setCaretLineVisible(true);
    sciPtr->setCaretLineBackgroundColor(QColor(240, 240, 240));
    sciPtr->setScrollWidthTracking(true);
    sciPtr->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);
    sciPtr->setScrollWidth(20);

    QsciLexer* lexer = sciPtr->lexer();
    const bool showLineNumber = settings_.value("editor/showLineNumber", true).toBool();
    sciPtr->setMarginLineNumbers(MarginLineNum, showLineNumber);

    const QString editorCharFont = settings_.value("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);

    const bool bold = settings_.value("editor/bold", false).toBool();
    font.setBold(bold);
    const bool italic = settings_.value("editor/italic", false).toBool();
    font.setItalic(italic);
    const bool underline = settings_.value("editor/underline", false).toBool();
    font.setUnderline(underline);

    const int editorCharSize = settings_.value("editor/editorCharSize", 13).toInt();
    font.setPointSize(editorCharSize);
    lexer->setFont(font);

    const QString editorCharColor = settings_.value("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);
    lexer->setColor(color, 0);

    const QString editorBGColor = settings_.value("editor/editorBGColor", "#FFFFFF").toString();
    QColor bgcolor;
    bgcolor.setNamedColor(editorBGColor);
    lexer->setPaper(bgcolor);
}

QsciScintillaPtr ConfigMgr::createSciObject(const QString& text, QWidget* parent)
{
    QsciScintillaPtr sciObject = std::make_shared<QsciScintilla>(parent);
    QsciLexer* lexer = new QsciLexerCem();
    sciObject->setLexer(lexer);
    sciObject->setText(text);
    configSciObject(sciObject);

    return sciObject;
}

void ConfigMgr::setProperty(const QString &key, const QVariant &value)
{
    settings_.setValue(key, value);
}

QVariant ConfigMgr::getProperty(const QString &key, const QVariant &defaultValue) const
{
    return settings_.value(key, defaultValue);
}

}
