#ifndef AUDIO_PITCHER_WAVE_H
#define AUDIO_PITCHER_WAVE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

/* .wav file header structure. */
struct WaveHeader
{
    char   RIFF[4];
    std::uint32_t DataLength;
    char   WAVE[4];
    char   fmt_[4];
    std::uint32_t SubBlockLength;
    std::uint16_t formatTag;
    std::uint16_t Channels;
    std::uint32_t SampFreq;
    std::uint32_t BytesPerSec;
    std::uint16_t BytesPerSamp;
    std::uint16_t BitsPerSamp;
    char   data[4];
    std::uint32_t WaveSize;
};

class Wave
{
public:
    Wave(const std::string& filename);
    ~Wave();

    void load(const std::string& filename);

    void save(const std::string& newfilename);
    void savefft(const std::string& newfilename, float* dataf);

    static void splitBytes(short twoBytes, unsigned char & lb, unsigned char & hb);
    static void decode16bit(std::vector<double>& channel, short* data, std::size_t channelSize);
    static void decode8bit(std::vector<double>& channel, short* data, std::size_t channelSize);
    static void encode16bit(const std::vector<double>& source, short* data, std::size_t dataSize);
    static void encode8bit(const std::vector<double>& source, short* data, std::size_t dataSize);

    unsigned int getWaveSize() const
    {
        return header.WaveSize;
    }

    virtual unsigned short getBitsPerSample() const
    {
        return header.BitsPerSamp;
    }

    unsigned int getBytesPerSample() const
    {
        return header.BytesPerSamp;
    }

    unsigned int getBytesPerSec() const
    {
        return header.BytesPerSec;
    }

    bool isStereo() const
    {
        return 2 == getChannelsNum();
    }

    bool isMono() const
    {
        return 1 == getChannelsNum();
    }

    unsigned short getChannelsNum() const
    {
        return header.Channels;
    }

    std::string getFilename() const
    {
        return filepath;
    }

    static double sampleAt(std::vector<double> dataSource, std::size_t pos)
    {
        return dataSource[pos];
    }

//protected:
    std::vector<double> dataSource;
    WaveHeader header;
private:
    std::string filepath;
};


#endif //AUDIO_PITCHER_WAVE_H
