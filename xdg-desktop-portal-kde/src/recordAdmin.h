//pts: （int64_t）显示时间，结合AVStream->time_base转换成时间戳
//dts: （int64_t）解码时间，结合AVStream->time_base转换成时间戳
#ifndef RECORDADMIN_H
#define RECORDADMIN_H
#include "AVInputStream.h"
#include "AVOutputStream.h"
#include "writeFrameThread.h"
#include <sys/time.h>
#include <map>
#include <qimage.h>
#include "AVInputStream.h"
#include "AVInputStream.h"
#include "gifrecord.h"
#include "waylandintegration.h"
#include "waylandintegration_p.h"
#include "writeFrameThread.h"
#define AUDIO_INPUT_DEVICE    "hw:0,0"
#define VIDEO_INPUT_DEVICE    "/dev/video0"
#include <QThread>

extern "C"
{
#include <libavdevice/avdevice.h>
}

using namespace std;
class RecordAdmin :public QObject
{
    Q_OBJECT

public:
    RecordAdmin(int &argc, char **argv,WaylandIntegration::WaylandIntegrationPrivate* context,QObject *parent = nullptr);
    virtual ~RecordAdmin();

public:
    /**
     * @brief init:初始化录屏管理
     * @param screenWidth:原图宽度
     * @param screenHeight:原图高度
     * @param fps:帧率
     * @param audioType:音频类型
     * @param x:x坐标
     * @param y:y坐标
     * @param selectWidth:选择的宽度
     * @param selectHeight:选择的高度
     * @param path:视频保存路径
     */
    void init(int screenWidth, int screenHeight);

    /**
     * @brief stopStream:停止录屏
     * @return
     */
    int stopStream();

protected:
    void  setRecordAudioType(int audioType);
    void  setMicAudioRecord(bool bRecord);
    void  setSysAudioRecord(bool bRecord);
    int   startStream();
    static void* stream(void* param);

public:
    CAVInputStream                           *m_pInputStream;
    CAVOutputStream                          *m_pOutputStream;
    WaylandIntegration::WriteFrameThread     *m_writeFrameThread;
    WaylandIntegration::GifRecord            *m_pGifRecord;

private:
    WaylandIntegration::WaylandIntegrationPrivate* m_context;
    //参数列表：程序名称，视频类型，视频宽，视频高，视频x坐标，视频y坐标，视频帧率，视频保存路径，音频类型
    QList<QString> argvList;
    //文件路径
    QString m_filePath;
    //帧率
    int m_fps;
    //音频类型
    int m_audioType;
    //视频类型
    int  m_videoType;
    //x坐标
    int m_x;
    //y坐标
    int m_y;
    //帧宽
    int m_selectWidth;
    //帧高
    int m_selectHeight;
    pthread_t  m_mainThread;
};

#endif // RECORDADMIN_H