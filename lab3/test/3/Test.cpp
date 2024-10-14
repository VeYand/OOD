#include <gtest/gtest.h>
#include <vector>
#include "../../3/InputStream/CMemoryInputStream.h"
#include "../../3/InputStream/Decorator/CDecompressInputStream.h"
#include "../../3/InputStream/Decorator/CDecryptInputStream.h"
#include "../../3/OutputStream/CMemoryOutputStream.h"
#include "../../3/OutputStream/Decorator/CCompressOutputStream.h"
#include "../../3/OutputStream/Decorator/CEncryptOutputStream.h"

TEST(CMemoryInputStream, ReadByteWorksCorrectly)
{

}

TEST(CMemoryInputStream, ReadBlockWorksCorrectly)
{
}

TEST(CMemoryOutputStream, WriteByteWorksCorrectly)
{
}

TEST(CMemoryOutputStream, WriteBlockWorksCorrectly)
{
}

TEST(CCompressOutputStream, CompressesDataCorrectly)
{
}

TEST(CDecompressInputStream, DecompressesDataCorrectly)
{
}

TEST(CEncryptDecryptStream, EncryptsAndDecryptsDataCorrectly)
{
}

TEST(CMemoryInputStream, CloseStreamCorrectly)
{
}

TEST(CMemoryOutputStream, CloseStreamCorrectly)
{
}
