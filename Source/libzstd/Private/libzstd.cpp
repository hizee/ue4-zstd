// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "libzstd.h"

#include "zstd.h"

#define LOCTEXT_NAMESPACE "FlibzstdModule"
#define DEFAULT_COMPRESSION_LEVEL 3

int32 FZstdCompressionFormat::Level = DEFAULT_COMPRESSION_LEVEL;

FName FZstdCompressionFormat::GetCompressionFormatName()
{
	return TEXT("zstd");
}

bool FZstdCompressionFormat::Compress(void* CompressedBuffer, int32& CompressedSize, const void* UncompressedBuffer, int32 UncompressedSize, int32 CompressionData)
{
	UE_LOG(LogTemp, Log, TEXT("FZstdCompressionFormat::Compress level is %d"), FZstdCompressionFormat::Level);
	int32 Result = ZSTD_compress(CompressedBuffer, CompressedSize, UncompressedBuffer, UncompressedSize, FZstdCompressionFormat::Level);
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
	return ZSTD_compressBound(UncompressedSize);
}

#define ZSTD_LEVEL_OPTION_STRING TEXT("-ZstdLevel=")
void FlibzstdModule::StartupModule()
{
	FString CommandLine = FCommandLine::Get();
	if (CommandLine.Contains(ZSTD_LEVEL_OPTION_STRING, ESearchCase::IgnoreCase))
	{
		int32 level;
		FParse::Value(FCommandLine::Get(), *FString(ZSTD_LEVEL_OPTION_STRING).ToLower(), level);
		FZstdCompressionFormat::Level = FMath::Clamp(level, ZSTD_minCLevel(),ZSTD_maxCLevel());
	}

	ZstdCompressionFormat = new FZstdCompressionFormat();
	IModularFeatures::Get().RegisterModularFeature(COMPRESSION_FORMAT_FEATURE_NAME, ZstdCompressionFormat);

}

void FlibzstdModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(COMPRESSION_FORMAT_FEATURE_NAME, ZstdCompressionFormat);
	delete ZstdCompressionFormat;

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FlibzstdModule, libzstd)