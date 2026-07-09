/*
 * File  : FfmpegCommandBuilder.h
 * Author: Mark Documento
 */

#ifndef _Croon_FfmpegCommandBuilder_h_
#define _Croon_FfmpegCommandBuilder_h_

#include "FfmpegAudioCommandBuilder.h"
#include "FfmpegExportCommandBuilder.h"
#include "FfmpegProjectCommandBuilder.h"
#include "FfmpegThumbnailCommandBuilder.h"

struct FfmpegCommandBuilder {
    static Vector<String> ConvertAudioToVorbis(String audioPath, String outputPath) {
        return FfmpegAudioCommandBuilder::ConvertToVorbis(audioPath, outputPath);
    }
    
    static Vector<String> DehissAudio(String audioPath, String outputPath, int factor=30) {
        return FfmpegAudioCommandBuilder::Dehiss(audioPath, outputPath, factor);
    }
    
    static Vector<String> DumpAttachmentAndGenerateThumbnail(String projectPath, String infoFilePath, String outputPath, int width, int height) {
        return FfmpegProjectCommandBuilder::DumpAttachmentAndGenerateThumbnail(projectPath, infoFilePath, outputPath, width, height);
    }
    
    static Vector<String> ExportWithBackgroundVideo(const KarData& data, String assFilePath, String outputPath, String audioFilepath="", bool preview=true) {
        return FfmpegExportCommandBuilder::WithBackgroundVideo(data, assFilePath, outputPath, audioFilepath, preview);
    }
    
    static Vector<String> ExportWithVisualization(const KarData& data, String assFilePath, String outputPath, String audioFilepath, bool preview=true) {
        return FfmpegExportCommandBuilder::WithVisualization(data, assFilePath, outputPath, audioFilepath, preview);
    }
    
    static Vector<String> GenerateCoverImage(String videoPath, String outputPath, double thumbnailTS) {
        return FfmpegExportCommandBuilder::GenerateCoverImage(videoPath, outputPath, thumbnailTS);
    }
    
    static Vector<String> GenerateThumbnail(String videoPath, String outputPath, int width, int height) {
        return FfmpegThumbnailCommandBuilder::Generate(videoPath, outputPath, width, height);
    }
    
    static Vector<String> ProjectExtractAudioAndInfo(String projectPath, String audioFilePath, String infoFilePath) {
        return FfmpegProjectCommandBuilder::ExtractAudioAndInfo(projectPath, audioFilePath, infoFilePath);
    }
    
    static Vector<String> ProjectExtractVideo(String projectPath, String videoFilePath) {
        return FfmpegProjectCommandBuilder::ExtractVideo(projectPath, videoFilePath);
    }
    
    static Vector<String> ProjectSaveWithBackgroundVideo(const KarData& data, String outputPath) {
        return FfmpegProjectCommandBuilder::SaveWithBackgroundVideo(data, outputPath);
    }
    
    static Vector<String> ProjectSaveWithVisualization(const KarData& data, String outputPath) {
        return FfmpegProjectCommandBuilder::SaveWithVisualization(data, outputPath);
    }
};

#endif
