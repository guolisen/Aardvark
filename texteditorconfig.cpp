#include "texteditorconfig.h"
#include <QSettings>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercem.h>

TextEditorConfig::TextEditorConfig()
{

}

void TextEditorConfig::Config(QsciScintilla* textSci)
{
    if (!textSci)
        return;

    textSci_ = textSci;
    QsciLexer* lexer = textSci_->lexer();
    concreteLexer_ = dynamic_cast<QsciLexerCem*>(lexer);
    if (!concreteLexer_)
        return;

    textSci_->setMarginType(0, QsciScintilla::NumberMargin);
    textSci_->setMarginWidth(0,40);
    textSci_->setCaretLineVisible(true);
    textSci_->setCaretLineBackgroundColor(QColor(240, 240, 240));
    textSci_->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);
    textSci_->setScrollWidth(20);

    textSci_->setMarginType(1, QsciScintilla::SymbolMargin);
    textSci_->setMarginMarkerMask(1, QsciScintilla::SC_MASK_FOLDERS);
    textSci_->setFolding(QsciScintilla::BoxedTreeFoldStyle, 1);
    textSci_->setScrollWidthTracking(true);

    readSetting();
}

void TextEditorConfig::readSetting()
{
    QSettings settings;

    const bool showLineNumber = settings.value("editor/showLineNumber", true).toBool();
    textSci_->setMarginLineNumbers(0, showLineNumber);

    const QString editorCharFont = settings.value("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);

    const bool bold = settings.value("editor/bold", false).toBool();
    font.setBold(bold);
    const bool italic = settings.value("editor/italic", false).toBool();
    font.setItalic(italic);
    const bool underline = settings.value("editor/underline", false).toBool();
    font.setUnderline(underline);

    const int editorCharSize = settings.value("editor/editorCharSize", 13).toInt();
    font.setPointSize(editorCharSize);
    concreteLexer_->setFont(font);

    const QString editorCharColor = settings.value("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);
    concreteLexer_->setColor(color, 0);

    const QString editorBGColor = settings.value("editor/editorBGColor", "#FFFFFF").toString();
    QColor bgcolor;
    bgcolor.setNamedColor(editorBGColor);
    concreteLexer_->setPaper(bgcolor);
}
