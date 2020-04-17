// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "libzstd.h"

#define LOCTEXT_NAMESPACE "FlibzstdModule"

FName FZstdCompressionFormat::GetCompressionFormatName()
{
	return TEXT("zstd");
}
bool FZstdCompressionFormat::Compress(void* CompressedBuffer, int32& CompressedSize, const void* UncompressedBuffer, int32 UncompressedSize, int32 CompressionData)
{

	return false;
}
bool FZstdCompressionFormat::Uncompress(void* UncompressedBuffer, int32& UncompressedSize, const void* CompressedBuffer, int32 CompressedSize, int32 CompressionData)
{
	return false;
}
int32 FZstdCompressionFormat::GetCompressedBufferSize(int32 UncompressedSize, int32 CompressionData)
{
	return 0;
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