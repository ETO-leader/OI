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

template<typename _Ty>
constexpr auto bswap(_Ty res){
    assert(is_integral_v<_Ty>);
    if(sizeof(_Ty)==2) res=__builtin_bswap16(res);
    if(sizeof(_Ty)==4) res=__builtin_bswap32(res);
    if(sizeof(_Ty)==8) res=__builtin_bswap64(res);
    return res;
}

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
        res=bswap(res);
        return res;
    }
    template<typename _Ty>
    auto putInt(_Ty x){
        assert(is_integral_v<_Ty>);
        x=bswap(x);
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

enum Ether_Type{
    IPv4=0x0800,
    ARP=0x0806
};

class ARP_header{
public:
    uint16_t headware_type;
    uint16_t protocol_type;
    uint8_t HLEN;
    uint8_t PLEN;
    uint16_t OPcode;
    array<uint16_t,3> SHA;
    uint32_t SPA;
    array<uint16_t,3> THA;
    uint32_t TPA;
};

class IPv4_header{
public:
    uint8_t IHL;                    // 4b in fact
    uint8_t type;
    uint16_t total_length;
    uint16_t identification;
    uint16_t offset;                // 13b in fact
    uint8_t TTL;
    uint8_t protocol;
    uint16_t header_checksum;
    uint32_t source_IPaddress;
    uint32_t destination_IPaddress;
    vector<uint8_t> opnion;
};

class CRC32{
private:
    auto CRC(vector<uint8_t>&a){
        auto cur=(uint64_t)(0);
        auto pos=0;
        cir(i,0,4) a.emplace_back(0);
        cir(i,0,32) (cur<<=1)|=((a[pos>>3]>>(pos&7))&1),++pos;
        cur^=numeric_limits<uint32_t>::max();
        const auto num=0b1'00000100'11000001'00011101'10110111ll;
        for(;pos<(int)(a.size()<<3);++pos){
            (cur<<=1)|=((a[pos>>3]>>(pos&7))&1);
            if((cur>>32)&1) cur^=num;
        }
        vector<int> resw(4);
        resw[0]=(cur>>24)&255;
        resw[1]=(cur>>16)&255;
        resw[2]=(cur>>8)&255;
        resw[3]=cur&255;
        for(auto&i:resw) i^=255;
        for(auto&i:resw){
            auto w=i;i=0;
            cir(c,0,8) i|=(((w>>c)&1)<<(7-c));
        }
        return (resw[0]<<24)|(resw[1]<<16)|(resw[2]<<8)|resw[3];
    }
    friend class CRC_constructor;
public:
    auto check(vector<uint8_t>&data){
        auto dcrc=(uint32_t)(0);
        cir(i,(int)(data.size())-4,(int)(data.size())) (dcrc<<=8)|=data[i];
        cir(i,0,4) data.pop_back();
        return CRC(data)==dcrc;
    }
} CRC_checker;

class IPv4_header_checker{
private:
    template<typename _Ty>
    auto to_basic_string(_Ty num){
        static_assert(is_integral_v<_Ty>);
        basic_string<uint8_t> res;
        num=bswap(num);
        cir(i,0,sizeof(num)) res+=(num&255),num>>=8;
        return res;
    }
    auto expand(IPv4_header hdr){
        basic_string<uint8_t> bytes;
        bytes+=to_basic_string<uint8_t>(hdr.IHL|0b01000000);
        bytes+=to_basic_string(hdr.type);
        bytes+=to_basic_string(hdr.total_length);
        bytes+=to_basic_string(hdr.identification);
        bytes+=to_basic_string<uint16_t>(hdr.offset|0b0100000000000000);
        bytes+=to_basic_string(hdr.TTL);
        bytes+=to_basic_string(hdr.protocol);
        bytes+=to_basic_string(hdr.header_checksum);
        bytes+=to_basic_string(hdr.source_IPaddress);
        bytes+=to_basic_string(hdr.destination_IPaddress);
        for(auto&x:hdr.opnion) bytes+=x;
        return bytes;
    }
    auto compress(basic_string<uint8_t> data){
        vector<uint16_t> res;
        cir(i,0,(int)(data.size())/2) res.emplace_back((data[i*2]<<8)|data[i*2+1]);
        return res;
    }
    auto sum(uint16_t a,uint16_t b){
        if(!b) return a;
        return sum(a+b,((uint32_t)(a)+(uint32_t)(b))>>16);
    }
    friend class IPv4_constructor;
public:
    auto check(IPv4_header hdr){
        const auto last_chk=hdr.header_checksum;
        hdr.header_checksum=0;
        const auto arr=compress(expand(hdr));
        auto chk=(uint16_t)(0);
        for(auto&i:arr) chk=sum(chk,i);
        chk^=numeric_limits<uint16_t>::max();
        return chk==last_chk;
    }
} IPv4_checker;

class data_checker{
private:
    auto type(const vector<uint8_t>&data){
        return (data[12]<<8)|data[13];
    }
    auto split_data(const vector<uint8_t>&data){
        vector<uint8_t> res;
        cir(p,14,(int)(data.size())-4) res.emplace_back(data[p]);
        return res;
    }
    auto get_header(const vector<uint8_t>&data){
        auto hdr=IPv4_header();
        auto rdpos=0;
        auto readInt=[&](auto&x){
            cir(i,0,sizeof(x)) (x<<=8)|=(data[rdpos]),++rdpos;
        };
        readInt(hdr.IHL);
        hdr.IHL&=((1u<<4)-1);
        readInt(hdr.type);
        readInt(hdr.total_length);
        readInt(hdr.identification);
        readInt(hdr.offset);
        hdr.offset&=((1u<<13)-1);
        readInt(hdr.TTL);
        readInt(hdr.protocol);
        readInt(hdr.header_checksum);
        readInt(hdr.source_IPaddress);
        readInt(hdr.destination_IPaddress);
        cir(i,0,(hdr.IHL*4)-20){
            uint8_t info;readInt(info);
            hdr.opnion.emplace_back(info);
        }
        return hdr;
    }
public:
    auto check(vector<uint8_t>&data){
        if(!CRC_checker.check(data)) return false;
        if(type(data)==IPv4){
            data=split_data(data);
            const auto hdr=get_header(data);
            if(!IPv4_checker.check(hdr)) return false;
        }
        return true;
    }
} data_checker;

class CRC_constructor{
public:
    auto construct(vector<uint8_t>&data){
        const auto w=CRC_checker.CRC(data);
        data.emplace_back((w>>24)&255);
        data.emplace_back((w>>16)&255);
        data.emplace_back((w>>8)&255);
        data.emplace_back(w&255);
    }
};

class IPv4_constructor{
public:
    auto construct(IPv4_header&hdr){
        hdr.header_checksum=0;
        const auto arr=IPv4_checker.compress(IPv4_checker.expand(hdr));
        auto chk=(uint16_t)(0);
        for(auto&i:arr) chk=IPv4_checker.sum(chk,i);
        chk^=numeric_limits<uint16_t>::max();
        hdr.header_checksum=chk;
    }
};

int main(){
    auto[hdr,data]=IO.read_data();
    for(auto&[dhdr,_data]:data){
        cout<<(data_checker.check(_data)?"Yes":"No")<<'\n';
    }
    return 0;
}

