// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Misc/ICompressionFormat.h"

struct FZstdCompressionFormat : public ICompressionFormat
{
	virtual FName GetCompressionFormatName()override;
	virtual bool Compress(void* CompressedBuffer, int32& CompressedSize, const void* UncompressedBuffer, int32 UncompressedSize, int32 CompressionData)override;
	virtual bool Uncompress(void* UncompressedBuffer, int32& UncompressedSize, const void* CompressedBuffer, int32 CompressedSize, int32 CompressionData)override;
	virtual int32 GetCompressedBufferSize(int32 UncompressedSize, int32 CompressionData)override;

	static int32 Level;
};

class FlibzstdModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FZstdCompressionFormat* ZstdCompressionFormat;
};
