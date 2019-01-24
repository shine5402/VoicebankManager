# Configure outside librarys' include path here.

unix|win32: LIBS += -L$$PWD/../../libchardet-1.0.5/lib/ -llibchardet -llibchardet.dll

INCLUDEPATH += $$PWD/../../libchardet-1.0.5/include/chardet
DEPENDPATH += $$PWD/../../libchardet-1.0.5/include/chardet

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ImageCropper-release/ -lImageCropper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ImageCropper-release/ -lImageCropperd
else:unix: LIBS += -L$$PWD/../ImageCropper-release/ -lImageCropper

INCLUDEPATH += $$PWD/../ImageCropper/include
DEPENDPATH += $$PWD/../ImageCropper/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LeafLogger-release/ -lLeafLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LeafLogger-release/ -lLeafLoggerd
else:unix: LIBS += -L$$PWD/../LeafLogger-release/ -lLeafLogger

INCLUDEPATH += $$PWD/../LeafLogger/include
DEPENDPATH += $$PWD/../LeafLogger/include

INCLUDEPATH += $$PWD/../SetOperations/include
