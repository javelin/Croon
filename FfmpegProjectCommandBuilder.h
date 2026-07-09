/*
 * File  : FfmpegProjectCommandBuilder.h
 * Author: Mark Documento
 */

#ifndef _Croon_FfmpegProjectCommandBuilder_h_
#define _Croon_FfmpegProjectCommandBuilder_h_

#include "AppIdentity.h"
#include "KarData.h"

struct FfmpegProjectCommandBuilder {
    static Vector<String> DumpAttachmentAndGenerateThumbnail(String projectPath, String infoFilePath, String outputPath, int width, int height) {
        return {
            "-dump_attachment:t:0", infoFilePath,
            "-i", projectPath,
            "-map", "v:0",
            "-ss", "00:00:01",
            "-vframes", "1",
            "-vf",
            Format("crop='min(iw,ih)':'min(iw,ih)',scale=%d:%d",
                    width, height),
            outputPath
        };
    }
    
    static Vector<String> ExtractAudioAndInfo(String projectPath, String audioFilePath, String infoFilePath) {
        return {
            "-dump_attachment:t:0", infoFilePath,
            "-i", projectPath,
            "-map", "0:a:0",
            "-c:a", "copy",
            audioFilePath
        };
    }
    
    static Vector<String> ExtractVideo(String projectPath, String videoFilePath) {
        return {
            "-i", projectPath,
            "-map", "0:v:0",
            "-c:v", "copy",
            videoFilePath
        };
    }
    
    static Vector<String> SaveWithBackgroundVideo(const KarData& data, String outputPath) {
        return {
            "-i", data.videoFilePath,
            "-i", data.audioFilePath,
            "-map", "0:v:0",
            "-map", "1:a:0",
            "-map_metadata:s", "-1",
            "-attach", data.infoFilePath,
            "-metadata:s:2", AppIdentity::ProjectAttachmentMetadata(),
            "-metadata:s:2", "mimetype=application/json",
            "-c", "copy",
            "-metadata", Format("APPLICATION=%s v%s", AppIdentity::ProductName(), data.version),
            "-f", "matroska",
            outputPath
        };
    }
    
    static Vector<String> SaveWithVisualization(const KarData& data, String outputPath) {
        return {
            "-i", data.audioFilePath,
            "-map_metadata:s", "-1",
            "-attach", data.infoFilePath,
            "-metadata:s:1", AppIdentity::ProjectAttachmentMetadata(),
            "-metadata:s:1", "mimetype=application/json",
            "-c", "copy",
            "-metadata", Format("APPLICATION=%s v%s", AppIdentity::ProductName(), data.version),
            "-f", "matroska",
            outputPath
        };
    }
};

#endif
