#include "lang.hpp"




void Item::Init()
{
};

Item::Item()
{
    Init();
};

Item::~Item()
{
};

Item::Item(const Item& tc)
{
    Init();
    *this = tc;
};

Item& Item::operator=(const Item& tc)
{
    if(this!=&tc)
    {
        m_ddd = tc.m_ddd;
    }
    return *this;
};


const Item::DDDPair& Item::GetDDD() const
{
    return m_ddd;
};

void Item::SetDDD(const DDDPair& dddp)
{
    m_ddd = dddp;
};



///////////////////////////////////////////////////////////////////
Content::Content(){};


void Content::read(const std::string& file)
{
    
    //test for existance
    int ret = access(file.c_str(), F_OK);
    if(ret != 0)
    {
        std::string err("Cannot access file ");
        err += file;
        perror(err.c_str());
        exit(1);
    }

    //open file to read
    std::ifstream in(file.c_str(), std::ios_base::in);
    if( !in.is_open() )
    {
        printf("cannot open file: %s", file.c_str());
        exit(1);
    }


    char buff[20000];

    while( !in.eof() )
    {
        in.getline(buff, 20000);
        std::string sline(buff);
        size_t pos = sline.find("@");
        if(pos == std::string::npos)
            continue;

        std::string dew = sline.substr(0, pos);
        
        size_t pos1 = sline.find("@", pos+1);
        if(pos1 == std::string::npos)
            pos1 = sline.size();

        std::string row = sline.substr(pos+1, pos1-pos);

        Item it;
        it.SetDDD(Item::DDDPair(dew, row));
        
        m_vec.push_back(it);
    };//while

    

    //close file
    in.close();
};

void Content::write(const std::string& file)
{

};


void Content::show_ddd(bool show_de) const
{
    float count(.0), right(.0);
    for(std::vector<Item>::const_iterator it = m_vec.begin(); it != m_vec.end(); ++it)
    {
        const Item& item = *it;
        const Item::DDDPair& ddp = item.GetDDD();
        const std::string& dew = ddp.first;
        const std::string& row = ddp.second;


        std::string first, second;
        char buf[1000];
        if(show_de)
        {
            first = dew;
            second = row;
        }
        else
        {
            first = row;
            second = dew;
        }


        printf("\n\n");
        printf("\n%s = %s", show_de == true ? "DE" : "RO", first.c_str());//show w to test
        printf("\n%s = ", show_de == true ? "RO" : "DE");//to be typed by user

        std::cin.getline(buf, 1000);
        //scanf("%s", buf);
        std::string sbuf(buf);        
        

        if(!show_de)//test if in DE is ok
        {
            if(sbuf == second)//exact match
            {
                printf("%s - gut!", second.c_str());
                printf("  %.0f%c", (++right * 100) / ++count, '%');
            }
            else
            {
                printf("nicht gut! - %s", second.c_str());
                printf("  %.0f%c", (right * 100) / ++count, '%');
            }

        }
        else
        {//test if in RO is ok
            std::string second2 = misc::tolower(second);
            std::string sbuf2 = misc::tolower(sbuf);

           if(sbuf2 == second2)//exact match
           {
                printf("%s - gut!", second.c_str());
                printf("  %.0f%c", (++right * 100) / ++count, '%');
           }
            else
           {
                printf("nicht gut! - %s", second.c_str());
                printf("  %.0f%c", (right * 100) / ++count, '%');
           }
        } 
                
    }//for
};

//////////////////////////////////////////////////////////////
