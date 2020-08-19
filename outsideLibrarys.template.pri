# Configure outside librarys' include path here.
# This project needs libchardet, ImageCropper, LeafLogger, SetOperation, TextCodecUtils.
# Qt Creator's "Add Library" function can help.
# Don't forget to rename this file to "outsideLibrary.pri"

INCLUDEPATH += $$PWD/../SetOperations/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/TextCodecUtils-release/ -lTextCodecUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/TextCodecUtils-release/ -lTextCodecUtilsd
else:unix: LIBS += -L$$PWD/../../QtSharedLibraryReleases/TextCodecUtils-release/ -lTextCodecUtils

INCLUDEPATH += $$PWD/../../QtSharedLibraryReleases/TextCodecUtils-release/include
DEPENDPATH += $$PWD/../../QtSharedLibraryReleases/TextCodecUtils-release/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/LeafLogger-release/ -lLeafLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/LeafLogger-release/ -lLeafLoggerd
else:unix: LIBS += -L$$PWD/../../QtSharedLibraryReleases/LeafLogger-release/ -lLeafLogger

INCLUDEPATH += $$PWD/../../QtSharedLibraryReleases/LeafLogger-release/include
DEPENDPATH += $$PWD/../../QtSharedLibraryReleases/LeafLogger-release/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/ImageCropper-release/ -lImageCropper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QtSharedLibraryReleases/ImageCropper-release/ -lImageCropperd
else:unix: LIBS += -L$$PWD/../../QtSharedLibraryReleases/ImageCropper-release/ -lImageCropper

INCLUDEPATH += $$PWD/../../QtSharedLibraryReleases/ImageCropper-release/include
DEPENDPATH += $$PWD/../../QtSharedLibraryReleases/ImageCropper-release/include


win32: LIBS += -L$$PWD/../../3rdPartyLibrary/libchardet-1.0.5/lib/ -lchardet -lchardet.dll
else:unix:LIBS += -L$$PWD/../../3rdPartyLibrary/libchardet-1.0.5/lib/ -lchardet

INCLUDEPATH += $$PWD/../../3rdPartyLibrary/libchardet-1.0.5/include/chardet
DEPENDPATH += $$PWD/../../3rdPartyLibrary/libchardet-1.0.5/include/chardet