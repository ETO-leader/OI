#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class pcap_header_t{
public:
    uint32_t magic_number;  // 用于文件类型识别，始终为 0xA1B2C3D4，
    uint16_t version_major; // 始终为 2
    uint16_t version_minor; // 始终为 4
    int32_t thiszone;       // 始终为 0
    uint32_t sigfigs;       // 始终为 0
    uint32_t snaplen;       // 允许的最大包长度，始终为 262144
    uint32_t network;       // 数据类型，本次学习题中始终为 1 （以太网）
    pcap_header_t(
        uint32_t _magic_number=0xA1B2C3D4,
        uint32_t _version_major=2,
        uint32_t _version_minor=4,
        uint32_t _thiszone=0,
        uint32_t _sigfigs=0,
        uint32_t _snaplen=262144,
        uint32_t _network=1
    ):
        magic_number(_magic_number),
        version_major(_version_major),
        version_minor(_version_minor),
        thiszone(_thiszone),
        sigfigs(_sigfigs),
        snaplen(_snaplen),
        network(_network){}
};

class pcap_record_header_t{
public:
    uint32_t ts_sec;        // 时间戳（秒）
    uint32_t ts_usec;       // 时间戳（微秒）
    uint32_t incl_len;      // 该片段的存储长度
    uint32_t orig_len;      // 该片段实际的长度
    pcap_record_header_t()=default;
    pcap_record_header_t(
        uint32_t _ts_sec,
        uint32_t _ts_usec,
        uint32_t _incl_len,
        uint32_t _orig_len
    ):
        ts_sec(_ts_sec),
        ts_usec(_ts_usec),
        incl_len(_incl_len),
        orig_len(_orig_len){}
};

class pcapIO{
private:
    class EOF_signal{};
    template<typename _Ty>
    auto readInt() const{
        assert(is_integral_v<_Ty>);
        auto res=_Ty(0);
        const auto succ=fread(&res,sizeof(res),1,stdin);
        if(succ!=1) throw EOF_signal();
        if(sizeof(_Ty)==2) res=__builtin_bswap16(res);
        if(sizeof(_Ty)==4) res=__builtin_bswap32(res);
        if(sizeof(_Ty)==8) res=__builtin_bswap64(res);
        return res;
    }
    template<typename _Ty>
    auto putInt(_Ty x){
        assert(is_integral_v<_Ty>);
        if(sizeof(_Ty)==2) x=__builtin_bswap16(x);
        if(sizeof(_Ty)==4) x=__builtin_bswap32(x);
        if(sizeof(_Ty)==8) x=__builtin_bswap64(x);
        fwrite(&x,sizeof(_Ty),1,stdout);
    }
public:
    auto read_data(){
        auto hdr=pcap_header_t();
        hdr.magic_number=readInt<uint32_t>();
        hdr.version_major=readInt<uint16_t>();
        hdr.version_minor=readInt<uint16_t>();
        hdr.thiszone=readInt<int32_t>();
        hdr.sigfigs=readInt<uint32_t>();
        hdr.snaplen=readInt<uint32_t>();
        hdr.network=readInt<uint32_t>();
        vector<pair<pcap_record_header_t,vector<uint8_t>>> data;
        while(true){
            try{
                pcap_record_header_t x;
                x.ts_sec=readInt<uint32_t>();
                x.ts_usec=readInt<uint32_t>();
                x.incl_len=readInt<uint32_t>();
                x.orig_len=readInt<uint32_t>();
                vector<uint8_t> _data(x.incl_len);
                for(auto&w:_data) w=readInt<uint8_t>();
                data.emplace_back(x,_data);
            }catch(EOF_signal){
                break;
            }
        }
        return pair(hdr,data);
    }
    auto write_data(pcap_header_t hdr,vector<pair<pcap_record_header_t,vector<uint8_t>>> data){
        putInt(hdr.magic_number);
        putInt(hdr.version_major);
        putInt(hdr.version_minor);
        putInt(hdr.thiszone);
        putInt(hdr.sigfigs);
        putInt(hdr.snaplen);
        putInt(hdr.network);
        for(auto&[x,_data]:data){
            putInt(x.ts_sec);
            putInt(x.ts_usec);
            putInt(x.incl_len);
            putInt(x.orig_len);
            for(auto&w:_data) putInt(w);
        }
    }
} IO;

int main(){
    auto[hdr,data]=IO.read_data();
    sort(data.begin(),data.end(),[&](auto&a,auto&b){
        return a.first.ts_sec==b.first.ts_sec?
            a.first.ts_usec<b.first.ts_usec:
            a.first.ts_sec<b.first.ts_sec;
    });
    const auto rdata=data;
    data.clear();
    for(auto&[x,_data]:rdata) if(x.orig_len<1001) data.emplace_back(x,_data);
    IO.write_data(hdr,data);
    return 0;
}

