/*
 * File  : AudioPlayerBase.h
 * Author: Mark Documento
 */

#ifndef _Croon_AudioPlayerBase_h_
#define _Croon_AudioPlayerBase_h_

enum AudioPlayerEventType {
    APE_Type_Close,
    APE_Type_Play,
    APE_Type_Pause,
    APE_Type_Seek,
    APE_Type_Seek_Fwd,
    APE_Type_Seek_Backwd,
    APE_Type_Volume,
    APE_Type_Volume_Up,
    APE_Type_Volume_Dn
};

class AudioPlayerEvent : public Pte<AudioPlayerEvent> {
public:
    AudioPlayerEvent(const AudioPlayerEvent& e) : type(e.type), data(e.data) {}
    AudioPlayerEvent(AudioPlayerEventType type) : type(type), data(0) {}
    AudioPlayerEvent(AudioPlayerEventType type, double data) : type(type), data(data) {}
    AudioPlayerEventType Type() const { return type; }
    double Data() const { return data; }
private:
    AudioPlayerEventType type;
    double data;
};

struct IAudioPlayer {
	enum AudioPlayerState {
        Playing = 0,
        Paused,
        Closed
    };
    virtual const String& LastError() const = 0;
    virtual bool Open(const String& filename) = 0;
    virtual bool Pause() = 0;
    virtual bool Play() = 0;
    virtual bool Seek(double seconds) = 0;
    virtual bool Close() = 0;
    virtual bool IsPlaying() = 0;
    virtual bool IsOpen() = 0;
    virtual bool Reopen() = 0;
    virtual double Duration() = 0;
    virtual double Position() = 0;
    virtual AudioPlayerState State() = 0;
    virtual String GetPath() const = 0;
    
    Event<String> WhenError;
    Event<double> WhenProgress;
    Event<> WhenPlaybackDone;
};

class AudioPlayerBase : public IAudioPlayer {
public:
    AudioPlayerBase() : lastError("") {}
    virtual const String& LastError() const override { return lastError; }
	
protected:
    void LastError(const String& error) { lastError = error; }
	
protected:
    String lastError;
    bool opened;
    bool playing;
};

#endif
