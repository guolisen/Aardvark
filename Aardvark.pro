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
        View/mainwindow.cpp \
    View/logdocwindow.cpp \
    View/SettingPanel/epushbutton.cpp \
    View/SettingPanel/settingpanel.cpp \
    View/SettingPanel/fontform.cpp \
    Thirdparty/QScintilla/lexers/LexA68k.cpp \
    Thirdparty/QScintilla/lexers/LexAbaqus.cpp \
    Thirdparty/QScintilla/lexers/LexAda.cpp \
    Thirdparty/QScintilla/lexers/LexAPDL.cpp \
    Thirdparty/QScintilla/lexers/LexAsm.cpp \
    Thirdparty/QScintilla/lexers/LexAsn1.cpp \
    Thirdparty/QScintilla/lexers/LexASY.cpp \
    Thirdparty/QScintilla/lexers/LexAU3.cpp \
    Thirdparty/QScintilla/lexers/LexAVE.cpp \
    Thirdparty/QScintilla/lexers/LexAVS.cpp \
    Thirdparty/QScintilla/lexers/LexBaan.cpp \
    Thirdparty/QScintilla/lexers/LexBash.cpp \
    Thirdparty/QScintilla/lexers/LexBasic.cpp \
    Thirdparty/QScintilla/lexers/LexBatch.cpp \
    Thirdparty/QScintilla/lexers/LexBibTeX.cpp \
    Thirdparty/QScintilla/lexers/LexBullant.cpp \
    Thirdparty/QScintilla/lexers/LexCaml.cpp \
    Thirdparty/QScintilla/lexers/LexCLW.cpp \
    Thirdparty/QScintilla/lexers/LexCmake.cpp \
    Thirdparty/QScintilla/lexers/LexCem.cpp \
    Thirdparty/QScintilla/lexers/LexCOBOL.cpp \
    Thirdparty/QScintilla/lexers/LexCoffeeScript.cpp \
    Thirdparty/QScintilla/lexers/LexConf.cpp \
    Thirdparty/QScintilla/lexers/LexCPP.cpp \
    Thirdparty/QScintilla/lexers/LexCrontab.cpp \
    Thirdparty/QScintilla/lexers/LexCsound.cpp \
    Thirdparty/QScintilla/lexers/LexCSS.cpp \
    Thirdparty/QScintilla/lexers/LexD.cpp \
    Thirdparty/QScintilla/lexers/LexDiff.cpp \
    Thirdparty/QScintilla/lexers/LexDMAP.cpp \
    Thirdparty/QScintilla/lexers/LexDMIS.cpp \
    Thirdparty/QScintilla/lexers/LexECL.cpp \
    Thirdparty/QScintilla/lexers/LexEDIFACT.cpp \
    Thirdparty/QScintilla/lexers/LexEiffel.cpp \
    Thirdparty/QScintilla/lexers/LexErlang.cpp \
    Thirdparty/QScintilla/lexers/LexErrorList.cpp \
    Thirdparty/QScintilla/lexers/LexEScript.cpp \
    Thirdparty/QScintilla/lexers/LexFlagship.cpp \
    Thirdparty/QScintilla/lexers/LexForth.cpp \
    Thirdparty/QScintilla/lexers/LexFortran.cpp \
    Thirdparty/QScintilla/lexers/LexGAP.cpp \
    Thirdparty/QScintilla/lexers/LexGui4Cli.cpp \
    Thirdparty/QScintilla/lexers/LexHaskell.cpp \
    Thirdparty/QScintilla/lexers/LexHex.cpp \
    Thirdparty/QScintilla/lexers/LexHTML.cpp \
    Thirdparty/QScintilla/lexers/LexInno.cpp \
    Thirdparty/QScintilla/lexers/LexJSON.cpp \
    Thirdparty/QScintilla/lexers/LexKix.cpp \
    Thirdparty/QScintilla/lexers/LexKVIrc.cpp \
    Thirdparty/QScintilla/lexers/LexLaTeX.cpp \
    Thirdparty/QScintilla/lexers/LexLisp.cpp \
    Thirdparty/QScintilla/lexers/LexLout.cpp \
    Thirdparty/QScintilla/lexers/LexLua.cpp \
    Thirdparty/QScintilla/lexers/LexMagik.cpp \
    Thirdparty/QScintilla/lexers/LexMake.cpp \
    Thirdparty/QScintilla/lexers/LexMarkdown.cpp \
    Thirdparty/QScintilla/lexers/LexMatlab.cpp \
    Thirdparty/QScintilla/lexers/LexMetapost.cpp \
    Thirdparty/QScintilla/lexers/LexMMIXAL.cpp \
    Thirdparty/QScintilla/lexers/LexModula.cpp \
    Thirdparty/QScintilla/lexers/LexMPT.cpp \
    Thirdparty/QScintilla/lexers/LexMSSQL.cpp \
    Thirdparty/QScintilla/lexers/LexMySQL.cpp \
    Thirdparty/QScintilla/lexers/LexNimrod.cpp \
    Thirdparty/QScintilla/lexers/LexNsis.cpp \
    Thirdparty/QScintilla/lexers/LexNull.cpp \
    Thirdparty/QScintilla/lexers/LexOpal.cpp \
    Thirdparty/QScintilla/lexers/LexOScript.cpp \
    Thirdparty/QScintilla/lexers/LexPascal.cpp \
    Thirdparty/QScintilla/lexers/LexPB.cpp \
    Thirdparty/QScintilla/lexers/LexPerl.cpp \
    Thirdparty/QScintilla/lexers/LexPLM.cpp \
    Thirdparty/QScintilla/lexers/LexPO.cpp \
    Thirdparty/QScintilla/lexers/LexPOV.cpp \
    Thirdparty/QScintilla/lexers/LexPowerPro.cpp \
    Thirdparty/QScintilla/lexers/LexPowerShell.cpp \
    Thirdparty/QScintilla/lexers/LexProgress.cpp \
    Thirdparty/QScintilla/lexers/LexProps.cpp \
    Thirdparty/QScintilla/lexers/LexPS.cpp \
    Thirdparty/QScintilla/lexers/LexPython.cpp \
    Thirdparty/QScintilla/lexers/LexR.cpp \
    Thirdparty/QScintilla/lexers/LexRebol.cpp \
    Thirdparty/QScintilla/lexers/LexRegistry.cpp \
    Thirdparty/QScintilla/lexers/LexRuby.cpp \
    Thirdparty/QScintilla/lexers/LexRust.cpp \
    Thirdparty/QScintilla/lexers/LexScriptol.cpp \
    Thirdparty/QScintilla/lexers/LexSmalltalk.cpp \
    Thirdparty/QScintilla/lexers/LexSML.cpp \
    Thirdparty/QScintilla/lexers/LexSorcus.cpp \
    Thirdparty/QScintilla/lexers/LexSpecman.cpp \
    Thirdparty/QScintilla/lexers/LexSpice.cpp \
    Thirdparty/QScintilla/lexers/LexSQL.cpp \
    Thirdparty/QScintilla/lexers/LexSTTXT.cpp \
    Thirdparty/QScintilla/lexers/LexTACL.cpp \
    Thirdparty/QScintilla/lexers/LexTADS3.cpp \
    Thirdparty/QScintilla/lexers/LexTAL.cpp \
    Thirdparty/QScintilla/lexers/LexTCL.cpp \
    Thirdparty/QScintilla/lexers/LexTCMD.cpp \
    Thirdparty/QScintilla/lexers/LexTeX.cpp \
    Thirdparty/QScintilla/lexers/LexTxt2tags.cpp \
    Thirdparty/QScintilla/lexers/LexVB.cpp \
    Thirdparty/QScintilla/lexers/LexVerilog.cpp \
    Thirdparty/QScintilla/lexers/LexVHDL.cpp \
    Thirdparty/QScintilla/lexers/LexVisualProlog.cpp \
    Thirdparty/QScintilla/lexers/LexYAML.cpp \
    Thirdparty/QScintilla/lexlib/Accessor.cpp \
    Thirdparty/QScintilla/lexlib/CharacterCategory.cpp \
    Thirdparty/QScintilla/lexlib/CharacterSet.cpp \
    Thirdparty/QScintilla/lexlib/LexerBase.cpp \
    Thirdparty/QScintilla/lexlib/LexerModule.cpp \
    Thirdparty/QScintilla/lexlib/LexerNoExceptions.cpp \
    Thirdparty/QScintilla/lexlib/LexerSimple.cpp \
    Thirdparty/QScintilla/lexlib/PropSetSimple.cpp \
    Thirdparty/QScintilla/lexlib/StyleContext.cpp \
    Thirdparty/QScintilla/lexlib/WordList.cpp \
    Thirdparty/QScintilla/Qt4Qt5/InputMethod.cpp \
    Thirdparty/QScintilla/Qt4Qt5/ListBoxQt.cpp \
    Thirdparty/QScintilla/Qt4Qt5/MacPasteboardMime.cpp \
    Thirdparty/QScintilla/Qt4Qt5/PlatQt.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qsciabstractapis.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qsciapis.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscicommand.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscicommandset.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscidocument.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexer.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexeravs.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerbash.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerbatch.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercmake.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercoffeescript.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercpp.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercsharp.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercss.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercustom.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexercem.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerd.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerdiff.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexeredifact.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerfortran.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerfortran77.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerhtml.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexeridl.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerjava.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerjavascript.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerjson.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerlua.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexermakefile.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexermarkdown.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexermatlab.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexeroctave.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerpascal.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerperl.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerpo.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerpostscript.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerpov.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerproperties.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerpython.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerruby.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerspice.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexersql.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexertcl.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexertex.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerverilog.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexervhdl.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexerxml.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscilexeryaml.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscimacro.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qsciprinter.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qsciscintilla.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qsciscintillabase.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscistyle.cpp \
    Thirdparty/QScintilla/Qt4Qt5/qscistyledtext.cpp \
    Thirdparty/QScintilla/Qt4Qt5/SciAccessibility.cpp \
    Thirdparty/QScintilla/Qt4Qt5/SciClasses.cpp \
    Thirdparty/QScintilla/Qt4Qt5/ScintillaQt.cpp \
    Thirdparty/QScintilla/src/AutoComplete.cpp \
    Thirdparty/QScintilla/src/CallTip.cpp \
    Thirdparty/QScintilla/src/CaseConvert.cpp \
    Thirdparty/QScintilla/src/CaseFolder.cpp \
    Thirdparty/QScintilla/src/Catalogue.cpp \
    Thirdparty/QScintilla/src/CellBuffer.cpp \
    Thirdparty/QScintilla/src/CharClassify.cpp \
    Thirdparty/QScintilla/src/ContractionState.cpp \
    Thirdparty/QScintilla/src/Decoration.cpp \
    Thirdparty/QScintilla/src/Document.cpp \
    Thirdparty/QScintilla/src/EditModel.cpp \
    Thirdparty/QScintilla/src/Editor.cpp \
    Thirdparty/QScintilla/src/EditView.cpp \
    Thirdparty/QScintilla/src/ExternalLexer.cpp \
    Thirdparty/QScintilla/src/Indicator.cpp \
    Thirdparty/QScintilla/src/KeyMap.cpp \
    Thirdparty/QScintilla/src/LineMarker.cpp \
    Thirdparty/QScintilla/src/MarginView.cpp \
    Thirdparty/QScintilla/src/PerLine.cpp \
    Thirdparty/QScintilla/src/PositionCache.cpp \
    Thirdparty/QScintilla/src/RESearch.cpp \
    Thirdparty/QScintilla/src/RunStyles.cpp \
    Thirdparty/QScintilla/src/ScintillaBase.cpp \
    Thirdparty/QScintilla/src/Selection.cpp \
    Thirdparty/QScintilla/src/Style.cpp \
    Thirdparty/QScintilla/src/UniConversion.cpp \
    Thirdparty/QScintilla/src/ViewStyle.cpp \
    Thirdparty/QScintilla/src/XPM.cpp \
    Core/configmgr.cpp \
    Core/appcontext.cpp \
    View/addregexdialog.cpp

HEADERS += \
    View/mainwindow.h \
    View/logdocwindow.h \
    View/SettingPanel/epushbutton.h \
    View/SettingPanel/settingpanel.h \
    View/SettingPanel/fontform.h \
    Thirdparty/QScintilla/include/ILexer.h \
    Thirdparty/QScintilla/include/Platform.h \
    Thirdparty/QScintilla/include/Sci_Position.h \
    Thirdparty/QScintilla/include/SciLexer.h \
    Thirdparty/QScintilla/include/Scintilla.h \
    Thirdparty/QScintilla/include/ScintillaWidget.h \
    Thirdparty/QScintilla/lexlib/Accessor.h \
    Thirdparty/QScintilla/lexlib/CharacterCategory.h \
    Thirdparty/QScintilla/lexlib/CharacterSet.h \
    Thirdparty/QScintilla/lexlib/LexAccessor.h \
    Thirdparty/QScintilla/lexlib/LexerBase.h \
    Thirdparty/QScintilla/lexlib/LexerModule.h \
    Thirdparty/QScintilla/lexlib/LexerNoExceptions.h \
    Thirdparty/QScintilla/lexlib/LexerSimple.h \
    Thirdparty/QScintilla/lexlib/OptionSet.h \
    Thirdparty/QScintilla/lexlib/PropSetSimple.h \
    Thirdparty/QScintilla/lexlib/SparseState.h \
    Thirdparty/QScintilla/lexlib/StringCopy.h \
    Thirdparty/QScintilla/lexlib/StyleContext.h \
    Thirdparty/QScintilla/lexlib/SubStyles.h \
    Thirdparty/QScintilla/lexlib/WordList.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciabstractapis.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciapis.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscicommand.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscicommandset.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscidocument.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciglobal.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexer.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexeravs.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerbash.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerbatch.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercmake.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercoffeescript.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercpp.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercsharp.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercss.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercustom.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexercem.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerd.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerdiff.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexeredifact.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerfortran.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerfortran77.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerhtml.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexeridl.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerjava.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerjavascript.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerjson.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerlua.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexermakefile.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexermarkdown.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexermatlab.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexeroctave.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerpascal.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerperl.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerpo.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerpostscript.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerpov.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerproperties.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerpython.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerruby.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerspice.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexersql.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexertcl.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexertex.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerverilog.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexervhdl.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexerxml.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscilexeryaml.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscimacro.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciprinter.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciscintilla.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qsciscintillabase.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscistyle.h \
    Thirdparty/QScintilla/Qt4Qt5/Qsci/qscistyledtext.h \
    Thirdparty/QScintilla/Qt4Qt5/ListBoxQt.h \
    Thirdparty/QScintilla/Qt4Qt5/SciAccessibility.h \
    Thirdparty/QScintilla/Qt4Qt5/SciClasses.h \
    Thirdparty/QScintilla/Qt4Qt5/SciNamespace.h \
    Thirdparty/QScintilla/Qt4Qt5/ScintillaQt.h \
    Thirdparty/QScintilla/src/AutoComplete.h \
    Thirdparty/QScintilla/src/CallTip.h \
    Thirdparty/QScintilla/src/CaseConvert.h \
    Thirdparty/QScintilla/src/CaseFolder.h \
    Thirdparty/QScintilla/src/Catalogue.h \
    Thirdparty/QScintilla/src/CellBuffer.h \
    Thirdparty/QScintilla/src/CharClassify.h \
    Thirdparty/QScintilla/src/ContractionState.h \
    Thirdparty/QScintilla/src/Decoration.h \
    Thirdparty/QScintilla/src/Document.h \
    Thirdparty/QScintilla/src/EditModel.h \
    Thirdparty/QScintilla/src/Editor.h \
    Thirdparty/QScintilla/src/EditView.h \
    Thirdparty/QScintilla/src/ExternalLexer.h \
    Thirdparty/QScintilla/src/FontQuality.h \
    Thirdparty/QScintilla/src/Indicator.h \
    Thirdparty/QScintilla/src/KeyMap.h \
    Thirdparty/QScintilla/src/LineMarker.h \
    Thirdparty/QScintilla/src/MarginView.h \
    Thirdparty/QScintilla/src/Partitioning.h \
    Thirdparty/QScintilla/src/PerLine.h \
    Thirdparty/QScintilla/src/Position.h \
    Thirdparty/QScintilla/src/PositionCache.h \
    Thirdparty/QScintilla/src/RESearch.h \
    Thirdparty/QScintilla/src/RunStyles.h \
    Thirdparty/QScintilla/src/ScintillaBase.h \
    Thirdparty/QScintilla/src/Selection.h \
    Thirdparty/QScintilla/src/SparseVector.h \
    Thirdparty/QScintilla/src/SplitVector.h \
    Thirdparty/QScintilla/src/Style.h \
    Thirdparty/QScintilla/src/UnicodeFromUTF8.h \
    Thirdparty/QScintilla/src/UniConversion.h \
    Thirdparty/QScintilla/src/ViewStyle.h \
    Thirdparty/QScintilla/src/XPM.h \
    Core/configmgr.h \
    Core/commondefine.h \
    Core/appcontext.h \
    View/addregexdialog.h

FORMS += \
    View/mainwindow.ui \
    View/logdocwindow.ui \
    View/SettingPanel/fontform.ui \
    View/addregexdialog.ui

INCLUDEPATH += "Thirdparty/QScintilla" \
    "Thirdparty/QScintilla/lexlib" \
    "Thirdparty/QScintilla/src" \
    "Thirdparty/QScintilla/Qt4Qt5" \
    "Thirdparty/QScintilla/include"

#LIBS += -LE:/code/sci/QScintilla_gpl-2.10.8/build-Thirdparty/QScintilla-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug -lQScintilla2_qt5d

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


#TRANSLATIONS = \
#        Thirdparty/QScintilla_cs.ts \
#        Thirdparty/QScintilla_de.ts \
#        Thirdparty/QScintilla_es.ts \
 #       Thirdparty/QScintilla_fr.ts \
#        Thirdparty/QScintilla_pt_br.ts
