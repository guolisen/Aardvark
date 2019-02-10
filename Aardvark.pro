#-------------------------------------------------
#
# Project created by QtCreator 2019-02-06T22:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aardvark
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logdocwindow.cpp \
    SettingPanel/epushbutton.cpp \
    SettingPanel/settingpanel.cpp \
    SettingPanel/fontform.cpp \
    texteditorconfig.cpp \
    QScintilla/lexers/LexA68k.cpp \
    QScintilla/lexers/LexAbaqus.cpp \
    QScintilla/lexers/LexAda.cpp \
    QScintilla/lexers/LexAPDL.cpp \
    QScintilla/lexers/LexAsm.cpp \
    QScintilla/lexers/LexAsn1.cpp \
    QScintilla/lexers/LexASY.cpp \
    QScintilla/lexers/LexAU3.cpp \
    QScintilla/lexers/LexAVE.cpp \
    QScintilla/lexers/LexAVS.cpp \
    QScintilla/lexers/LexBaan.cpp \
    QScintilla/lexers/LexBash.cpp \
    QScintilla/lexers/LexBasic.cpp \
    QScintilla/lexers/LexBatch.cpp \
    QScintilla/lexers/LexBibTeX.cpp \
    QScintilla/lexers/LexBullant.cpp \
    QScintilla/lexers/LexCaml.cpp \
    QScintilla/lexers/LexCLW.cpp \
    QScintilla/lexers/LexCmake.cpp \
    QScintilla/lexers/LexCem.cpp \
    QScintilla/lexers/LexCOBOL.cpp \
    QScintilla/lexers/LexCoffeeScript.cpp \
    QScintilla/lexers/LexConf.cpp \
    QScintilla/lexers/LexCPP.cpp \
    QScintilla/lexers/LexCrontab.cpp \
    QScintilla/lexers/LexCsound.cpp \
    QScintilla/lexers/LexCSS.cpp \
    QScintilla/lexers/LexD.cpp \
    QScintilla/lexers/LexDiff.cpp \
    QScintilla/lexers/LexDMAP.cpp \
    QScintilla/lexers/LexDMIS.cpp \
    QScintilla/lexers/LexECL.cpp \
    QScintilla/lexers/LexEDIFACT.cpp \
    QScintilla/lexers/LexEiffel.cpp \
    QScintilla/lexers/LexErlang.cpp \
    QScintilla/lexers/LexErrorList.cpp \
    QScintilla/lexers/LexEScript.cpp \
    QScintilla/lexers/LexFlagship.cpp \
    QScintilla/lexers/LexForth.cpp \
    QScintilla/lexers/LexFortran.cpp \
    QScintilla/lexers/LexGAP.cpp \
    QScintilla/lexers/LexGui4Cli.cpp \
    QScintilla/lexers/LexHaskell.cpp \
    QScintilla/lexers/LexHex.cpp \
    QScintilla/lexers/LexHTML.cpp \
    QScintilla/lexers/LexInno.cpp \
    QScintilla/lexers/LexJSON.cpp \
    QScintilla/lexers/LexKix.cpp \
    QScintilla/lexers/LexKVIrc.cpp \
    QScintilla/lexers/LexLaTeX.cpp \
    QScintilla/lexers/LexLisp.cpp \
    QScintilla/lexers/LexLout.cpp \
    QScintilla/lexers/LexLua.cpp \
    QScintilla/lexers/LexMagik.cpp \
    QScintilla/lexers/LexMake.cpp \
    QScintilla/lexers/LexMarkdown.cpp \
    QScintilla/lexers/LexMatlab.cpp \
    QScintilla/lexers/LexMetapost.cpp \
    QScintilla/lexers/LexMMIXAL.cpp \
    QScintilla/lexers/LexModula.cpp \
    QScintilla/lexers/LexMPT.cpp \
    QScintilla/lexers/LexMSSQL.cpp \
    QScintilla/lexers/LexMySQL.cpp \
    QScintilla/lexers/LexNimrod.cpp \
    QScintilla/lexers/LexNsis.cpp \
    QScintilla/lexers/LexNull.cpp \
    QScintilla/lexers/LexOpal.cpp \
    QScintilla/lexers/LexOScript.cpp \
    QScintilla/lexers/LexPascal.cpp \
    QScintilla/lexers/LexPB.cpp \
    QScintilla/lexers/LexPerl.cpp \
    QScintilla/lexers/LexPLM.cpp \
    QScintilla/lexers/LexPO.cpp \
    QScintilla/lexers/LexPOV.cpp \
    QScintilla/lexers/LexPowerPro.cpp \
    QScintilla/lexers/LexPowerShell.cpp \
    QScintilla/lexers/LexProgress.cpp \
    QScintilla/lexers/LexProps.cpp \
    QScintilla/lexers/LexPS.cpp \
    QScintilla/lexers/LexPython.cpp \
    QScintilla/lexers/LexR.cpp \
    QScintilla/lexers/LexRebol.cpp \
    QScintilla/lexers/LexRegistry.cpp \
    QScintilla/lexers/LexRuby.cpp \
    QScintilla/lexers/LexRust.cpp \
    QScintilla/lexers/LexScriptol.cpp \
    QScintilla/lexers/LexSmalltalk.cpp \
    QScintilla/lexers/LexSML.cpp \
    QScintilla/lexers/LexSorcus.cpp \
    QScintilla/lexers/LexSpecman.cpp \
    QScintilla/lexers/LexSpice.cpp \
    QScintilla/lexers/LexSQL.cpp \
    QScintilla/lexers/LexSTTXT.cpp \
    QScintilla/lexers/LexTACL.cpp \
    QScintilla/lexers/LexTADS3.cpp \
    QScintilla/lexers/LexTAL.cpp \
    QScintilla/lexers/LexTCL.cpp \
    QScintilla/lexers/LexTCMD.cpp \
    QScintilla/lexers/LexTeX.cpp \
    QScintilla/lexers/LexTxt2tags.cpp \
    QScintilla/lexers/LexVB.cpp \
    QScintilla/lexers/LexVerilog.cpp \
    QScintilla/lexers/LexVHDL.cpp \
    QScintilla/lexers/LexVisualProlog.cpp \
    QScintilla/lexers/LexYAML.cpp \
    QScintilla/lexlib/Accessor.cpp \
    QScintilla/lexlib/CharacterCategory.cpp \
    QScintilla/lexlib/CharacterSet.cpp \
    QScintilla/lexlib/LexerBase.cpp \
    QScintilla/lexlib/LexerModule.cpp \
    QScintilla/lexlib/LexerNoExceptions.cpp \
    QScintilla/lexlib/LexerSimple.cpp \
    QScintilla/lexlib/PropSetSimple.cpp \
    QScintilla/lexlib/StyleContext.cpp \
    QScintilla/lexlib/WordList.cpp \
    QScintilla/Qt4Qt5/InputMethod.cpp \
    QScintilla/Qt4Qt5/ListBoxQt.cpp \
    QScintilla/Qt4Qt5/MacPasteboardMime.cpp \
    QScintilla/Qt4Qt5/PlatQt.cpp \
    QScintilla/Qt4Qt5/qsciabstractapis.cpp \
    QScintilla/Qt4Qt5/qsciapis.cpp \
    QScintilla/Qt4Qt5/qscicommand.cpp \
    QScintilla/Qt4Qt5/qscicommandset.cpp \
    QScintilla/Qt4Qt5/qscidocument.cpp \
    QScintilla/Qt4Qt5/qscilexer.cpp \
    QScintilla/Qt4Qt5/qscilexeravs.cpp \
    QScintilla/Qt4Qt5/qscilexerbash.cpp \
    QScintilla/Qt4Qt5/qscilexerbatch.cpp \
    QScintilla/Qt4Qt5/qscilexercmake.cpp \
    QScintilla/Qt4Qt5/qscilexercoffeescript.cpp \
    QScintilla/Qt4Qt5/qscilexercpp.cpp \
    QScintilla/Qt4Qt5/qscilexercsharp.cpp \
    QScintilla/Qt4Qt5/qscilexercss.cpp \
    QScintilla/Qt4Qt5/qscilexercustom.cpp \
    QScintilla/Qt4Qt5/qscilexercem.cpp \
    QScintilla/Qt4Qt5/qscilexerd.cpp \
    QScintilla/Qt4Qt5/qscilexerdiff.cpp \
    QScintilla/Qt4Qt5/qscilexeredifact.cpp \
    QScintilla/Qt4Qt5/qscilexerfortran.cpp \
    QScintilla/Qt4Qt5/qscilexerfortran77.cpp \
    QScintilla/Qt4Qt5/qscilexerhtml.cpp \
    QScintilla/Qt4Qt5/qscilexeridl.cpp \
    QScintilla/Qt4Qt5/qscilexerjava.cpp \
    QScintilla/Qt4Qt5/qscilexerjavascript.cpp \
    QScintilla/Qt4Qt5/qscilexerjson.cpp \
    QScintilla/Qt4Qt5/qscilexerlua.cpp \
    QScintilla/Qt4Qt5/qscilexermakefile.cpp \
    QScintilla/Qt4Qt5/qscilexermarkdown.cpp \
    QScintilla/Qt4Qt5/qscilexermatlab.cpp \
    QScintilla/Qt4Qt5/qscilexeroctave.cpp \
    QScintilla/Qt4Qt5/qscilexerpascal.cpp \
    QScintilla/Qt4Qt5/qscilexerperl.cpp \
    QScintilla/Qt4Qt5/qscilexerpo.cpp \
    QScintilla/Qt4Qt5/qscilexerpostscript.cpp \
    QScintilla/Qt4Qt5/qscilexerpov.cpp \
    QScintilla/Qt4Qt5/qscilexerproperties.cpp \
    QScintilla/Qt4Qt5/qscilexerpython.cpp \
    QScintilla/Qt4Qt5/qscilexerruby.cpp \
    QScintilla/Qt4Qt5/qscilexerspice.cpp \
    QScintilla/Qt4Qt5/qscilexersql.cpp \
    QScintilla/Qt4Qt5/qscilexertcl.cpp \
    QScintilla/Qt4Qt5/qscilexertex.cpp \
    QScintilla/Qt4Qt5/qscilexerverilog.cpp \
    QScintilla/Qt4Qt5/qscilexervhdl.cpp \
    QScintilla/Qt4Qt5/qscilexerxml.cpp \
    QScintilla/Qt4Qt5/qscilexeryaml.cpp \
    QScintilla/Qt4Qt5/qscimacro.cpp \
    QScintilla/Qt4Qt5/qsciprinter.cpp \
    QScintilla/Qt4Qt5/qsciscintilla.cpp \
    QScintilla/Qt4Qt5/qsciscintillabase.cpp \
    QScintilla/Qt4Qt5/qscistyle.cpp \
    QScintilla/Qt4Qt5/qscistyledtext.cpp \
    QScintilla/Qt4Qt5/SciAccessibility.cpp \
    QScintilla/Qt4Qt5/SciClasses.cpp \
    QScintilla/Qt4Qt5/ScintillaQt.cpp \
    QScintilla/src/AutoComplete.cpp \
    QScintilla/src/CallTip.cpp \
    QScintilla/src/CaseConvert.cpp \
    QScintilla/src/CaseFolder.cpp \
    QScintilla/src/Catalogue.cpp \
    QScintilla/src/CellBuffer.cpp \
    QScintilla/src/CharClassify.cpp \
    QScintilla/src/ContractionState.cpp \
    QScintilla/src/Decoration.cpp \
    QScintilla/src/Document.cpp \
    QScintilla/src/EditModel.cpp \
    QScintilla/src/Editor.cpp \
    QScintilla/src/EditView.cpp \
    QScintilla/src/ExternalLexer.cpp \
    QScintilla/src/Indicator.cpp \
    QScintilla/src/KeyMap.cpp \
    QScintilla/src/LineMarker.cpp \
    QScintilla/src/MarginView.cpp \
    QScintilla/src/PerLine.cpp \
    QScintilla/src/PositionCache.cpp \
    QScintilla/src/RESearch.cpp \
    QScintilla/src/RunStyles.cpp \
    QScintilla/src/ScintillaBase.cpp \
    QScintilla/src/Selection.cpp \
    QScintilla/src/Style.cpp \
    QScintilla/src/UniConversion.cpp \
    QScintilla/src/ViewStyle.cpp \
    QScintilla/src/XPM.cpp

HEADERS += \
        mainwindow.h \
    logdocwindow.h \
    SettingPanel/epushbutton.h \
    SettingPanel/settingpanel.h \
    SettingPanel/fontform.h \
    texteditorconfig.h \
    QScintilla/include/ILexer.h \
    QScintilla/include/Platform.h \
    QScintilla/include/Sci_Position.h \
    QScintilla/include/SciLexer.h \
    QScintilla/include/Scintilla.h \
    QScintilla/include/ScintillaWidget.h \
    QScintilla/lexlib/Accessor.h \
    QScintilla/lexlib/CharacterCategory.h \
    QScintilla/lexlib/CharacterSet.h \
    QScintilla/lexlib/LexAccessor.h \
    QScintilla/lexlib/LexerBase.h \
    QScintilla/lexlib/LexerModule.h \
    QScintilla/lexlib/LexerNoExceptions.h \
    QScintilla/lexlib/LexerSimple.h \
    QScintilla/lexlib/OptionSet.h \
    QScintilla/lexlib/PropSetSimple.h \
    QScintilla/lexlib/SparseState.h \
    QScintilla/lexlib/StringCopy.h \
    QScintilla/lexlib/StyleContext.h \
    QScintilla/lexlib/SubStyles.h \
    QScintilla/lexlib/WordList.h \
    QScintilla/Qt4Qt5/Qsci/qsciabstractapis.h \
    QScintilla/Qt4Qt5/Qsci/qsciapis.h \
    QScintilla/Qt4Qt5/Qsci/qscicommand.h \
    QScintilla/Qt4Qt5/Qsci/qscicommandset.h \
    QScintilla/Qt4Qt5/Qsci/qscidocument.h \
    QScintilla/Qt4Qt5/Qsci/qsciglobal.h \
    QScintilla/Qt4Qt5/Qsci/qscilexer.h \
    QScintilla/Qt4Qt5/Qsci/qscilexeravs.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerbash.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerbatch.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercmake.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercoffeescript.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercpp.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercsharp.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercss.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercustom.h \
    QScintilla/Qt4Qt5/Qsci/qscilexercem.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerd.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerdiff.h \
    QScintilla/Qt4Qt5/Qsci/qscilexeredifact.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerfortran.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerfortran77.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerhtml.h \
    QScintilla/Qt4Qt5/Qsci/qscilexeridl.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerjava.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerjavascript.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerjson.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerlua.h \
    QScintilla/Qt4Qt5/Qsci/qscilexermakefile.h \
    QScintilla/Qt4Qt5/Qsci/qscilexermarkdown.h \
    QScintilla/Qt4Qt5/Qsci/qscilexermatlab.h \
    QScintilla/Qt4Qt5/Qsci/qscilexeroctave.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerpascal.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerperl.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerpo.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerpostscript.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerpov.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerproperties.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerpython.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerruby.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerspice.h \
    QScintilla/Qt4Qt5/Qsci/qscilexersql.h \
    QScintilla/Qt4Qt5/Qsci/qscilexertcl.h \
    QScintilla/Qt4Qt5/Qsci/qscilexertex.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerverilog.h \
    QScintilla/Qt4Qt5/Qsci/qscilexervhdl.h \
    QScintilla/Qt4Qt5/Qsci/qscilexerxml.h \
    QScintilla/Qt4Qt5/Qsci/qscilexeryaml.h \
    QScintilla/Qt4Qt5/Qsci/qscimacro.h \
    QScintilla/Qt4Qt5/Qsci/qsciprinter.h \
    QScintilla/Qt4Qt5/Qsci/qsciscintilla.h \
    QScintilla/Qt4Qt5/Qsci/qsciscintillabase.h \
    QScintilla/Qt4Qt5/Qsci/qscistyle.h \
    QScintilla/Qt4Qt5/Qsci/qscistyledtext.h \
    QScintilla/Qt4Qt5/ListBoxQt.h \
    QScintilla/Qt4Qt5/SciAccessibility.h \
    QScintilla/Qt4Qt5/SciClasses.h \
    QScintilla/Qt4Qt5/SciNamespace.h \
    QScintilla/Qt4Qt5/ScintillaQt.h \
    QScintilla/src/AutoComplete.h \
    QScintilla/src/CallTip.h \
    QScintilla/src/CaseConvert.h \
    QScintilla/src/CaseFolder.h \
    QScintilla/src/Catalogue.h \
    QScintilla/src/CellBuffer.h \
    QScintilla/src/CharClassify.h \
    QScintilla/src/ContractionState.h \
    QScintilla/src/Decoration.h \
    QScintilla/src/Document.h \
    QScintilla/src/EditModel.h \
    QScintilla/src/Editor.h \
    QScintilla/src/EditView.h \
    QScintilla/src/ExternalLexer.h \
    QScintilla/src/FontQuality.h \
    QScintilla/src/Indicator.h \
    QScintilla/src/KeyMap.h \
    QScintilla/src/LineMarker.h \
    QScintilla/src/MarginView.h \
    QScintilla/src/Partitioning.h \
    QScintilla/src/PerLine.h \
    QScintilla/src/Position.h \
    QScintilla/src/PositionCache.h \
    QScintilla/src/RESearch.h \
    QScintilla/src/RunStyles.h \
    QScintilla/src/ScintillaBase.h \
    QScintilla/src/Selection.h \
    QScintilla/src/SparseVector.h \
    QScintilla/src/SplitVector.h \
    QScintilla/src/Style.h \
    QScintilla/src/UnicodeFromUTF8.h \
    QScintilla/src/UniConversion.h \
    QScintilla/src/ViewStyle.h \
    QScintilla/src/XPM.h

FORMS += \
    mainwindow.ui \
    logdocwindow.ui \
    SettingPanel/fontform.ui

INCLUDEPATH += "E:/code/qt/Aardvark/QScintilla" \
    "E:/code/qt/Aardvark/QScintilla/lexlib" \
    "E:/code/qt/Aardvark/QScintilla/src" \
    "E:/code/qt/Aardvark/QScintilla/Qt4Qt5" \
    "E:/code/qt/Aardvark/QScintilla/include"

#LIBS += -LE:/code/sci/QScintilla_gpl-2.10.8/build-qscintilla-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug -lqscintilla2_qt5d

DEFINES += SCINTILLA_QT SCI_LEXER

greaterThan(QT_MAJOR_VERSION, 4) {
        QT += widgets printsupport

    greaterThan(QT_MINOR_VERSION, 1) {
            macx:QT += macextras
    }

    # Work around QTBUG-39300.
    CONFIG -= android_install
} else {
    DEFINES += QT_NO_ACCESSIBILITY
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

#TRANSLATIONS = \
#        qscintilla_cs.ts \
#        qscintilla_de.ts \
#        qscintilla_es.ts \
 #       qscintilla_fr.ts \
#        qscintilla_pt_br.ts
