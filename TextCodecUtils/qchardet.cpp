#include "qchardet.h"
#include <chardet.h>
QTextCodec *QChardet::encodingForByteArray(QByteArray data,float* confidence)
{
    DetectObj *detectObj;
    if ((detectObj = detect_obj_init()) != nullptr)
    {
        char *charData = new char[static_cast<unsigned int>(data.size()) + 1];
        strcpy(charData, data.data());
        switch (detect_r(charData,strlen(charData),&detectObj))
        {
        case CHARDET_OUT_OF_MEMORY :
            LeafLogger::LogMessage("libchardet: On handle processing, occured out of memory\n");
            detect_obj_free (&detectObj);
            return nullptr;
        case CHARDET_NULL_OBJECT :
            LeafLogger::LogMessage("libchardet: 2st argument of chardet() is must memory allocation with detect_obj_init API\n");
            return nullptr;
        }
        if (confidence)
            *confidence = detectObj->confidence;
        return QTextCodec::codecForName(detectObj->encoding);
    }
    else
        return nullptr;
}
