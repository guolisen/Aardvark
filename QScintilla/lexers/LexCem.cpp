// Scintilla source code edit control
/** @file LexCem.cxx
 ** Lexer for Cem
 **/
// Copyright 2019 by Lewis Guo <cristian [dot] adam [at] gmx [dot] net>
// based on the NSIS lexer
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "CharacterSet.h"
#include "LexerModule.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

static bool isCemNumber(char ch)
{
    return(ch >= '0' && ch <= '9');
}

static bool isCemChar(char ch)
{
    return(ch == '.' ) || (ch == '_' ) || isCemNumber(ch) || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool isCemLetter(char ch)
{
    return(ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool CemNextLineHasElse(Sci_PositionU start, Sci_PositionU end, Accessor &styler)
{
    Sci_Position nNextLine = -1;
    for ( Sci_PositionU i = start; i < end; i++ ) {
        char cNext = styler.SafeGetCharAt( i );
        if ( cNext == '\n' ) {
            nNextLine = i+1;
            break;
        }
    }

    if ( nNextLine == -1 ) // We never foudn the next line...
        return false;

    for ( Sci_PositionU firstChar = nNextLine; firstChar < end; firstChar++ ) {
        char cNext = styler.SafeGetCharAt( firstChar );
        if ( cNext == ' ' )
            continue;
        if ( cNext == '\t' )
            continue;
        if ( styler.Match(firstChar, "ELSE")  || styler.Match(firstChar, "else"))
            return true;
        break;
    }

    return false;
}

static int calculateFoldCem(Sci_PositionU start, Sci_PositionU end, int foldlevel, Accessor &styler, bool bElse)
{
    // If the word is too long, it is not what we are looking for
    if ( end - start > 20 )
        return foldlevel;

    int newFoldlevel = foldlevel;

    char s[20]; // The key word we are looking for has atmost 13 characters
    for (unsigned int i = 0; i < end - start + 1 && i < 19; i++) {
        s[i] = static_cast<char>( styler[ start + i ] );
        s[i + 1] = '\0';
    }

    if ( CompareCaseInsensitive(s, "IF") == 0 || CompareCaseInsensitive(s, "WHILE") == 0
         || CompareCaseInsensitive(s, "MACRO") == 0 || CompareCaseInsensitive(s, "FOREACH") == 0
         || CompareCaseInsensitive(s, "ELSEIF") == 0 )
        newFoldlevel++;
    else if ( CompareCaseInsensitive(s, "ENDIF") == 0 || CompareCaseInsensitive(s, "ENDWHILE") == 0
              || CompareCaseInsensitive(s, "ENDMACRO") == 0 || CompareCaseInsensitive(s, "ENDFOREACH") == 0)
        newFoldlevel--;
    else if ( bElse && CompareCaseInsensitive(s, "ELSEIF") == 0 )
        newFoldlevel++;
    else if ( bElse && CompareCaseInsensitive(s, "ELSE") == 0 )
        newFoldlevel++;

    return newFoldlevel;
}

static int classifyWordCem(Sci_PositionU start, Sci_PositionU end, WordList *keywordLists[], Accessor &styler )
{
    char word[100] = {0};
    char lowercaseWord[100] = {0};

    WordList &Commands = *keywordLists[0];
    WordList &Parameters = *keywordLists[1];
    WordList &UserDefined = *keywordLists[2];

    for (Sci_PositionU i = 0; i < end - start + 1 && i < 99; i++) {
        word[i] = static_cast<char>( styler[ start + i ] );
        lowercaseWord[i] = static_cast<char>(tolower(word[i]));
    }

    // Check for special words...
    if ( CompareCaseInsensitive(word, "MACRO") == 0 || CompareCaseInsensitive(word, "ENDMACRO") == 0 )
        return SCE_CMAKE_MACRODEF;

    if ( CompareCaseInsensitive(word, "IF") == 0 ||  CompareCaseInsensitive(word, "ENDIF") == 0 )
        return SCE_CMAKE_IFDEFINEDEF;

    if ( CompareCaseInsensitive(word, "ELSEIF") == 0  || CompareCaseInsensitive(word, "ELSE") == 0 )
        return SCE_CMAKE_IFDEFINEDEF;

    if ( CompareCaseInsensitive(word, "WHILE") == 0 || CompareCaseInsensitive(word, "ENDWHILE") == 0)
        return SCE_CMAKE_WHILEDEF;

    if ( CompareCaseInsensitive(word, "FOREACH") == 0 || CompareCaseInsensitive(word, "ENDFOREACH") == 0)
        return SCE_CMAKE_FOREACHDEF;

    if ( Commands.InList(lowercaseWord) )
        return SCE_CMAKE_COMMANDS;

    if ( Parameters.InList(word) )
        return SCE_CMAKE_PARAMETERS;


    if ( UserDefined.InList(word) )
        return SCE_CMAKE_USERDEFINED;

    if ( strlen(word) > 3 ) {
        if ( word[1] == '{' && word[strlen(word)-1] == '}' )
            return SCE_CMAKE_VARIABLE;
    }

    // To check for numbers
    if ( isCemNumber( word[0] ) ) {
        bool bHasSimpleCmakeNumber = true;
        for (unsigned int j = 1; j < end - start + 1 && j < 99; j++) {
            if ( !isCemNumber( word[j] ) ) {
                bHasSimpleCmakeNumber = false;
                break;
            }
        }

        if ( bHasSimpleCmakeNumber )
            return SCE_CMAKE_NUMBER;
    }

    return SCE_CMAKE_DEFAULT;
}


static void setCemState(StyleContext& sc, int targetState, int& perState)
{
    perState = sc.state;
    sc.SetState(targetState);
}

static void ColouriseQsciLexerCemDoc(Sci_PositionU startPos, Sci_Position length,  int initStyle, WordList *keywordLists[], Accessor &styler)
{
    Sci_PositionU endPos = startPos + length;
    StyleContext sc(startPos, endPos - startPos, initStyle, styler);
    bool newLine = true;
    int perviousState = SCE_CEM_DEFAULT;
    sc.state = SCE_CEM_DEFAULT;
    for (; sc.More(); sc.Forward()) {
        if (sc.atLineStart) {
            newLine = true;
            if (sc.state == SCE_CEM_LOG)
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
        }

        switch (sc.state) {
        case SCE_CEM_DEFAULT:
            if (isCemNumber(sc.ch) && newLine)
            {
                setCemState(sc, SCE_CEM_TIME, perviousState);
                newLine = false;
                continue;
            }
            if (sc.chPrev == '-' && perviousState == SCE_CEM_TIME)
            {
                sc.Forward(2);
                setCemState(sc, SCE_CEM_MODULENAME, perviousState);
                continue;
            }
            if (sc.chPrev == ']' && perviousState == SCE_CEM_MODULENAME)
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_LOGLEVEL, perviousState);
                continue;
            }
            if (sc.chPrev == ' ' && perviousState == SCE_CEM_LOGLEVEL)
            {
                sc.Forward(2);
                setCemState(sc, SCE_CEM_THREADDATA, perviousState);
                continue;
            }
            if (sc.ch == ' ' && sc.chPrev == ']' && !newLine)
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_TIME, perviousState);
                continue;
            }
            if (sc.chPrev == ':' && perviousState == SCE_CEM_FILENAME)
            {
                setCemState(sc, SCE_CEM_FILENAME_LINENUM, perviousState);
                continue;
            }
            if(sc.chPrev == ']' && perviousState == SCE_CEM_FILENAME_LINENUM)
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_LOG, perviousState);
                continue;
            }
            break;
        case SCE_CEM_TIME:
            if (sc.ch == '-')
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
            break;
        case SCE_CEM_MODULENAME:
            if (sc.ch == ']')
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
            break;
        case SCE_CEM_LOGLEVEL:
            if (sc.ch == ' ')
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
            break;
        case SCE_CEM_THREADDATA:
            if (sc.chNext == '}')
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_THREADID, perviousState);
            }
            break;
        case SCE_CEM_THREADID:
            if (sc.ch == ']')
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_FUNCTION, perviousState);
            }
            break;
        case SCE_CEM_FUNCTION:
            if (sc.ch == ' ')
            {
                sc.Forward();
                setCemState(sc, SCE_CEM_FILENAME, perviousState);
            }
            break;
        case SCE_CEM_FILENAME:
            if (sc.chNext == ':')
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
            break;
        case SCE_CEM_FILENAME_LINENUM:
            if (sc.ch == ']')
            {
                setCemState(sc, SCE_CEM_DEFAULT, perviousState);
            }
            break;
        }
    }

    sc.Complete();
}

static void FoldQsciLexerCemDoc(Sci_PositionU startPos, Sci_Position length, int, WordList *[], Accessor &styler)
{
    // No folding enabled, no reason to continue...
    if ( styler.GetPropertyInt("fold") == 0 )
        return;

    bool foldAtElse = styler.GetPropertyInt("fold.at.else", 0) == 1;

    Sci_Position lineCurrent = styler.GetLine(startPos);
    Sci_PositionU safeStartPos = styler.LineStart( lineCurrent );

    bool bArg1 = true;
    Sci_Position nWordStart = -1;

    int levelCurrent = SC_FOLDLEVELBASE;
    if (lineCurrent > 0)
        levelCurrent = styler.LevelAt(lineCurrent-1) >> 16;
    int levelNext = levelCurrent;

    for (Sci_PositionU i = safeStartPos; i < startPos + length; i++) {
        char chCurr = styler.SafeGetCharAt(i);

        if ( bArg1 ) {
            if ( nWordStart == -1 && (isCemLetter(chCurr)) ) {
                nWordStart = i;
            }
            else if ( isCemLetter(chCurr) == false && nWordStart > -1 ) {
                int newLevel = calculateFoldCem( nWordStart, i-1, levelNext, styler, foldAtElse);

                if ( newLevel == levelNext ) {
                    if ( foldAtElse ) {
                        if ( CemNextLineHasElse(i, startPos + length, styler) )
                            levelNext--;
                    }
                }
                else
                    levelNext = newLevel;
                bArg1 = false;
            }
        }

        if ( chCurr == '\n' ) {
            if ( bArg1 && foldAtElse) {
                if ( CemNextLineHasElse(i, startPos + length, styler) )
                    levelNext--;
            }

            // If we are on a new line...
            int levelUse = levelCurrent;
            int lev = levelUse | levelNext << 16;
            if (levelUse < levelNext )
                lev |= SC_FOLDLEVELHEADERFLAG;
            if (lev != styler.LevelAt(lineCurrent))
                styler.SetLevel(lineCurrent, lev);

            lineCurrent++;
            levelCurrent = levelNext;
            bArg1 = true; // New line, lets look at first argument again
            nWordStart = -1;
        }
    }

    int levelUse = levelCurrent;
    int lev = levelUse | levelNext << 16;
    if (levelUse < levelNext)
        lev |= SC_FOLDLEVELHEADERFLAG;
    if (lev != styler.LevelAt(lineCurrent))
        styler.SetLevel(lineCurrent, lev);
}

static const char * const QsciLexerCemWordLists[] = {
    "Commands",
    "Parameters",
    "UserDefined",
    0,
    0,};

LexerModule lmCem(SCLEX_CEM, ColouriseQsciLexerCemDoc, "cem", FoldQsciLexerCemDoc, QsciLexerCemWordLists);
