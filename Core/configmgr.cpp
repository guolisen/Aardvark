#include "configmgr.h"
#include <QSci/qsciscintilla.h>
#include <QSci/qscilexercem.h>

const int MarginLineNum = 0;
const int MarginFold = 1;
const int MarginMark = 2;

//ConfigMgr::ConfigMgr(QObject *parent):
    //settings_("./Config.ini", QSettings::IniFormat)
ConfigMgr::ConfigMgr(QObject *parent)
{

}

void ConfigMgr::configSciObject(QsciScintillaPtr sciPtr)
{
    sciPtr->setScrollWidthTracking(true);
    sciPtr->setMarginType(MarginLineNum, QsciScintilla::NumberMargin);
    sciPtr->setMarginWidth(MarginLineNum,40);
    sciPtr->setCaretLineVisible(true);
    sciPtr->setCaretLineBackgroundColor(QColor(240, 240, 240));
    sciPtr->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);
    sciPtr->setScrollWidth(20);

    sciPtr->setMarginType(MarginFold, QsciScintilla::SymbolMargin);
    sciPtr->setMarginMarkerMask(MarginFold, QsciScintilla::SC_MASK_FOLDERS);
    sciPtr->setFolding(QsciScintilla::BoxedTreeFoldStyle, MarginFold);

    sciPtr->setMarginType(MarginMark, QsciScintilla::SymbolMargin);
    sciPtr->setMarginWidth(MarginLineNum,20);

    QsciLexer* lexer = sciPtr->lexer();
    const bool showLineNumber = settings_.value("editor/showLineNumber", true).toBool();
    sciPtr->setMarginLineNumbers(0, showLineNumber);

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

QsciScintillaPtr ConfigMgr::createSciObject(QWidget* parent)
{
    QsciScintillaPtr sciObject = std::make_shared<QsciScintilla>(parent);
    QsciLexer* lexer = new QsciLexerCem();
    sciObject->setLexer(lexer);

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

