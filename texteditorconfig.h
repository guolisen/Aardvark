#ifndef TEXTEDITORCONFIG_H
#define TEXTEDITORCONFIG_H
#include <memory>
class QsciScintilla;
class QsciLexerCMake;
class ITextEditorConfig
{
public:
    virtual void Config(QsciScintilla*) = 0;
    virtual void readSetting() = 0;
};

typedef std::shared_ptr<ITextEditorConfig> TextEditorConfigPtr;

class TextEditorConfig: public ITextEditorConfig
{
public:
    TextEditorConfig();

    virtual void Config(QsciScintilla* textSci) override;
    virtual void readSetting() override;

private:
    QsciScintilla* textSci_;
    QsciLexerCMake* concreteLexer_;
};

#endif // TEXTEDITORCONFIG_H
