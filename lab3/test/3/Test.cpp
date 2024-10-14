#include <gtest/gtest.h>
#include <vector>
#include "../../3/InputStream/CMemoryInputStream.h"
#include "../../3/InputStream/Decorator/CDecompressInputStream.h"
#include "../../3/InputStream/Decorator/CDecryptInputStream.h"
#include "../../3/OutputStream/CMemoryOutputStream.h"
#include "../../3/OutputStream/Decorator/CCompressOutputStream.h"
#include "../../3/OutputStream/Decorator/CEncryptOutputStream.h"

template<typename Decorator, typename... Args>
auto MakeDecorator(const Args &... args)
{
	return [=]<typename T>(T &&b) {
		return std::make_unique<Decorator>(std::forward<T>(b), args...);
	};
}

template<typename Component, typename Decorator>
auto operator<<(Component &&component, const Decorator &decorate)
{
	return decorate(std::forward<Component>(component));
}

TEST(CMemoryInputStream, ReadByteWorksCorrectly)
{
	const std::vector<uint8_t> data = {1, 2, 3, 4, 5};
	CMemoryInputStream stream(data);

	EXPECT_EQ(stream.ReadByte(), 1);
	EXPECT_EQ(stream.ReadByte(), 2);
	EXPECT_EQ(stream.ReadByte(), 3);
	EXPECT_EQ(stream.ReadByte(), 4);
	EXPECT_EQ(stream.ReadByte(), 5);
	EXPECT_TRUE(stream.IsEOF());

	EXPECT_THROW(stream.ReadByte(), std::runtime_error);
}

TEST(CMemoryInputStream, ReadBlockWorksCorrectly)
{
	const std::vector<uint8_t> data = {1, 2, 3, 4, 5};
	CMemoryInputStream stream(data);

	uint8_t buffer[3];
	EXPECT_EQ(stream.ReadBlock(buffer, 3), 3);
	EXPECT_EQ(buffer[0], 1);
	EXPECT_EQ(buffer[1], 2);
	EXPECT_EQ(buffer[2], 3);

	EXPECT_EQ(stream.ReadBlock(buffer, 3), 2);
	EXPECT_EQ(buffer[0], 4);
	EXPECT_EQ(buffer[1], 5);
	EXPECT_TRUE(stream.IsEOF());

	EXPECT_THROW(stream.ReadBlock(buffer, 3), std::runtime_error);
}

TEST(CMemoryInputStream, ClosedCorrectly)
{
	const std::vector<uint8_t> data = {1, 2, 3, 4, 5};
	CMemoryInputStream stream(data);

	stream.Close();

	EXPECT_THROW(stream.ReadByte(), std::logic_error);
	EXPECT_THROW(stream.ReadBlock(nullptr, 1), std::logic_error);
	EXPECT_THROW(stream.IsEOF(), std::logic_error);
}

TEST(CMemoryOutputStream, WriteByteWorksCorrectly)
{
	CMemoryOutputStream stream;

	stream.WriteByte(10);
	stream.WriteByte(20);
	stream.WriteByte(30);

	const auto &data = stream.GetData();
	EXPECT_EQ(data.size(), 3);
	EXPECT_EQ(data[0], 10);
	EXPECT_EQ(data[1], 20);
	EXPECT_EQ(data[2], 30);
}

TEST(CMemoryOutputStream, WriteBlockWorksCorrectly)
{
	CMemoryOutputStream stream;

	const std::vector<uint8_t> data = {10, 20, 30, 40, 50};
	stream.WriteBlock(data.data(), data.size());

	const auto &result = stream.GetData();
	EXPECT_EQ(result.size(), data.size());
	EXPECT_EQ(result, data);
}

TEST(CMemoryOutputStream, ClosedCorrectly)
{
	CMemoryOutputStream stream;
	stream.Close();

	EXPECT_THROW(stream.WriteByte(10), std::logic_error);
	EXPECT_THROW(stream.WriteBlock(nullptr, 1), std::logic_error);
}

TEST(CompressStream, CompressByteCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CCompressOutputStream compressedStream(std::move(memoryStream));

	compressedStream.WriteByte(10);
	compressedStream.WriteByte(10);
	compressedStream.WriteByte(20);
	compressedStream.Close();

	std::unique_ptr<IInputDataStream> inputStream = std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData());
	inputStream = std::move(inputStream) << MakeDecorator<CDecompressInputStream>();

	EXPECT_EQ(inputStream->ReadByte(), 10);
	EXPECT_EQ(inputStream->ReadByte(), 10);
	EXPECT_EQ(inputStream->ReadByte(), 20);
}

TEST(CompressStream, CompressBlockCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CCompressOutputStream compressedStream(std::move(memoryStream));

	const std::vector<uint8_t> data = {10, 10, 20, 20, 20};
	compressedStream.WriteBlock(data.data(), 5);
	compressedStream.Close();
	std::unique_ptr<IInputDataStream> inputStream = std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData());
	inputStream = std::move(inputStream) << MakeDecorator<CDecompressInputStream>();

	std::vector<uint8_t> decompressedData(data.size());
	EXPECT_EQ(inputStream->ReadBlock(decompressedData.data(), decompressedData.size()), data.size());
	EXPECT_EQ(decompressedData, data);
}

TEST(EncryptStream, EncryptByteCorrectly)
{
	uint32_t key = 12345;
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CEncryptOutputStream encryptedStream(std::move(memoryStream), key);

	encryptedStream.WriteByte(42);
	encryptedStream.WriteByte(43);

	auto decryptedStream = MakeDecorator<CDecryptInputStream>(key)(
		std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData()));

	EXPECT_EQ(decryptedStream->ReadByte(), 42);
	EXPECT_EQ(decryptedStream->ReadByte(), 43);
}

TEST(EncryptStream, EncryptBlockCorrectly)
{
	uint32_t key = 12345;
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CEncryptOutputStream encryptedStream(std::move(memoryStream), key);

	const std::vector<uint8_t> data = {42, 43, 44, 45, 46};
	encryptedStream.WriteBlock(data.data(), data.size());
	encryptedStream.Close();

	auto decryptedStream = MakeDecorator<CDecryptInputStream>(key)(
		std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData()));

	std::vector<uint8_t> decryptedData(data.size());
	EXPECT_EQ(decryptedStream->ReadBlock(decryptedData.data(), decryptedData.size()), data.size());
	EXPECT_EQ(decryptedData, data);
}

TEST(CompressionTest, CompressesRepeatedSequences)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CCompressOutputStream compressStream(std::move(memoryStream));

	uint8_t data[] = {1, 1, 1, 1};
	compressStream.WriteBlock(data, sizeof(data));
	compressStream.Close();

	const std::vector<uint8_t> &compressedData = rawMemoryStream->GetData();
	EXPECT_EQ(compressedData.size(), 2);
	EXPECT_EQ(compressedData[0], 4);
	EXPECT_EQ(compressedData[1], 1);
}

TEST(DecompressionTest, DecompressesSimpleData)
{
	std::vector<uint8_t> compressedData = {4, 1};
	auto memoryStream = std::make_unique<CMemoryInputStream>(compressedData);
	CDecompressInputStream decompressStream(std::move(memoryStream));

	uint8_t decompressedData[4];
	decompressStream.ReadBlock(decompressedData, sizeof(decompressedData));

	uint8_t expectedData[] = {1, 1, 1, 1};
	EXPECT_EQ(memcmp(decompressedData, expectedData, sizeof(decompressedData)), 0);
}

TEST(DecompressionTest, DecompressesMixedData)
{
	std::vector<uint8_t> compressedData = {2, 2, 3, 3, 4, 4};
	auto memoryStream = std::make_unique<CMemoryInputStream>(compressedData);
	CDecompressInputStream decompressStream(std::move(memoryStream));

	std::vector<uint8_t> decompressedData(9);
	decompressStream.ReadBlock(decompressedData.data(), decompressedData.size());

	const std::vector<uint8_t> &expectedData = {2, 2, 3, 3, 3, 4, 4, 4, 4};
	EXPECT_EQ(expectedData, decompressedData);
}

TEST(CompressionTest, HandlesNonRepeatedDataCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CCompressOutputStream compressStream(std::move(memoryStream));

	uint8_t data[] = {5, 6, 7, 8};
	compressStream.WriteBlock(data, sizeof(data));
	compressStream.Close();

	const std::vector<uint8_t> &compressedData = rawMemoryStream->GetData();
	const std::vector<uint8_t> &expectedCompressedData = {1, 5, 1, 6, 1, 7, 1, 8};
	EXPECT_EQ(compressedData.size(), 8);
	EXPECT_EQ(compressedData, expectedCompressedData);
}

TEST(EncryptionTest, EncryptsDataCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	uint32_t encryptionKey = 12345;
	CEncryptOutputStream encryptStream(std::move(memoryStream), encryptionKey);

	uint8_t data[] = {1, 2, 3, 4, 5};
	encryptStream.WriteBlock(data, sizeof(data));
	encryptStream.Close();

	const std::vector<uint8_t> &encryptedData = rawMemoryStream->GetData();

	EXPECT_EQ(encryptedData.size(), sizeof(data));
	EXPECT_NE(memcmp(encryptedData.data(), data, sizeof(data)), 0);
}

TEST(DecryptionTest, DecryptsDataCorrectly)
{
	uint32_t encryptionKey = 12345;

	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CEncryptOutputStream encryptStream(std::move(memoryStream), encryptionKey);

	uint8_t originalData[] = {1, 2, 3, 4, 5};
	encryptStream.WriteBlock(originalData, sizeof(originalData));
	encryptStream.Close();

	auto encryptedMemoryStream = std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData());
	CDecryptInputStream decryptStream(std::move(encryptedMemoryStream), encryptionKey);

	uint8_t decryptedData[sizeof(originalData)];
	decryptStream.ReadBlock(decryptedData, sizeof(decryptedData));

	EXPECT_EQ(memcmp(decryptedData, originalData, sizeof(originalData)), 0);
}

TEST(EncryptDecryptTest, WorksTogether)
{
	uint32_t encryptionKey = 54321;

	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CEncryptOutputStream encryptStream(std::move(memoryStream), encryptionKey);

	uint8_t originalData[] = {10, 20, 30, 40, 50};
	encryptStream.WriteBlock(originalData, sizeof(originalData));
	encryptStream.Close();

	auto encryptedMemoryStream = std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData());
	CDecryptInputStream decryptStream(std::move(encryptedMemoryStream), encryptionKey);

	uint8_t decryptedData[sizeof(originalData)];
	decryptStream.ReadBlock(decryptedData, sizeof(decryptedData));

	EXPECT_EQ(memcmp(decryptedData, originalData, sizeof(originalData)), 0);
}

TEST(CompressionTest, CompressesBoundaryValuesCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CCompressOutputStream compressStream(std::move(memoryStream));

	uint8_t data[] = {0, 255, 255, 0};
	compressStream.WriteBlock(data, sizeof(data));
	compressStream.Close();

	const std::vector<uint8_t> &compressedData = rawMemoryStream->GetData();
	const std::vector<uint8_t> &expectedCompressedData = {1, 0, 2, 255, 1, 0};

	EXPECT_EQ(compressedData.size(), expectedCompressedData.size());
	EXPECT_EQ(compressedData, expectedCompressedData);
}

TEST(DecompressionTest, DecompressesBoundaryValuesCorrectly)
{
	std::vector<uint8_t> compressedData = {1, 0, 2, 255, 1, 0};
	auto memoryStream = std::make_unique<CMemoryInputStream>(compressedData);
	CDecompressInputStream decompressStream(std::move(memoryStream));

	uint8_t decompressedData[4];
	decompressStream.ReadBlock(decompressedData, sizeof(decompressedData));

	uint8_t expectedData[] = {0, 255, 255, 0};
	EXPECT_EQ(memcmp(decompressedData, expectedData, sizeof(decompressedData)), 0);
}

TEST(EncryptionTest, EncryptsBoundaryValuesCorrectly)
{
	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	uint32_t encryptionKey = 12345;
	CEncryptOutputStream encryptStream(std::move(memoryStream), encryptionKey);

	uint8_t data[] = {0, 255, 255, 0};
	encryptStream.WriteBlock(data, sizeof(data));
	encryptStream.Close();

	const std::vector<uint8_t> &encryptedData = rawMemoryStream->GetData();
	EXPECT_EQ(encryptedData.size(), sizeof(data));
	EXPECT_NE(memcmp(encryptedData.data(), data, sizeof(data)), 0);
}

TEST(DecryptionTest, DecryptsBoundaryValuesCorrectly)
{
	uint32_t encryptionKey = 12345;

	auto memoryStream = std::make_unique<CMemoryOutputStream>();
	auto rawMemoryStream = memoryStream.get();
	CEncryptOutputStream encryptStream(std::move(memoryStream), encryptionKey);

	uint8_t originalData[] = {0, 255, 255, 0};
	encryptStream.WriteBlock(originalData, sizeof(originalData));
	encryptStream.Close();

	auto encryptedMemoryStream = std::make_unique<CMemoryInputStream>(rawMemoryStream->GetData());
	CDecryptInputStream decryptStream(std::move(encryptedMemoryStream), encryptionKey);

	uint8_t decryptedData[sizeof(originalData)];
	decryptStream.ReadBlock(decryptedData, sizeof(decryptedData));

	EXPECT_EQ(memcmp(decryptedData, originalData, sizeof(originalData)), 0);
}
