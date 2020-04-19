// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "libzstd.h"

#include "zstd.h"

#define LOCTEXT_NAMESPACE "FlibzstdModule"
#define COMPRESS_LEVEL 19

FName FZstdCompressionFormat::GetCompressionFormatName()
{
	return TEXT("zstd");
}
bool FZstdCompressionFormat::Compress(void* CompressedBuffer, int32& CompressedSize, const void* UncompressedBuffer, int32 UncompressedSize, int32 CompressionData)
{
	//UE_LOG(LogTemp, Log, TEXT("FZstdCompressionFormat::Compress"));
	//UE_LOG(LogTemp, Log, TEXT("CompressedBuffer:%x,CompressedSize:%d,UnCompressedBuffer:%x,UnCompressedSize:%d,CompressionData:%d"),CompressedBuffer,CompressedSize,UncompressedBuffer,UncompressedSize,CompressionData);

	int32 Result = ZSTD_compress(CompressedBuffer, CompressedSize, UncompressedBuffer, UncompressedSize, COMPRESS_LEVEL);
	if (Result > 0)
	{
		if (Result > GetCompressedBufferSize(UncompressedSize, CompressionData))
		{
			FPlatformMisc::LowLevelOutputDebugStringf(TEXT("%d < %d"), Result, GetCompressedBufferSize(UncompressedSize, CompressionData));
			// we cannot safely go over the BufferSize needed!
			return false;
		}
		CompressedSize = Result;
		return true;
	}
	return false;
}
bool FZstdCompressionFormat::Uncompress(void* UncompressedBuffer, int32& UncompressedSize, const void* CompressedBuffer, int32 CompressedSize, int32 CompressionData)
{
	//UE_LOG(LogTemp, Log, TEXT("FZstdCompressionFormat::Uncompress"));
	//UE_LOG(LogTemp, Log, TEXT("UncompressedBuffer:%x,UncompressedSize:%d,CompressedBuffer:%x,CompressedSize:%d,CompressionData:%d"), UncompressedBuffer, UncompressedSize, CompressedBuffer, CompressedSize, CompressionData);

	int32 Result = ZSTD_decompress(UncompressedBuffer, UncompressedSize, CompressedBuffer, CompressedSize);
	if (Result > 0)
	{
		UncompressedSize = Result;
		return true;
	}
	return false;
}
int32 FZstdCompressionFormat::GetCompressedBufferSize(int32 UncompressedSize, int32 CompressionData)
{
	//UE_LOG(LogTemp, Log, TEXT("UncompressedSize:%d,CompressionData:%d"), UncompressedSize, CompressionData);
	//UE_LOG(LogTemp, Log, TEXT("FZstdCompressionFormat::GetCompressedBufferSize"));
	return ZSTD_compressBound(UncompressedSize);
}

void FlibzstdModule::StartupModule()
{
	ZstdCompressionFormat = new FZstdCompressionFormat();
	IModularFeatures::Get().RegisterModularFeature(COMPRESSION_FORMAT_FEATURE_NAME, ZstdCompressionFormat);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FlibzstdModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(COMPRESSION_FORMAT_FEATURE_NAME, ZstdCompressionFormat);
	delete ZstdCompressionFormat;
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FlibzstdModule, libzstd)