#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include <string>
#include <iomanip>
#include <math.h>
#include <cctype>
#include <map>
#define TRUE true
#define FALSE false
#define STR "string"
#define Boolean "bool"
#define Float "float"
#define INT "integer"
using namespace std;
using namespace boost;

class NA
{
private:
    string h;
public:

    NA (string f = ""):h(f){}
    NA operator = (string f){
        this->h = f;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const NA& self){
        return os << "NA";
    }


};
NA na;

class element{
    private:

        bool boolValue = 0;
        bool bool_index = 0;

        long num;
        bool num_index = 0;

        unsigned long bignum;
        bool bignum_index = 0;

        string str;
        bool str_index = 0;
        bool convertable = false;


        long double flo;
        bool float_index = 0;

        NA n;
        bool na_index = false;

        long double verify(){
            long double s;
            if(this->bignum_index){s=this->bignum;}
            else if(this->num_index){s=this->num;}
            else{s=this->flo;}
            return s;
        }
        
        void check_invertability(){
            int numofdots = 0;
            if (this->na_index){convertable = FALSE; return;}
            if (this->str_index)
            {

                for (const auto& e:this->str)
                {
                    
                    if (e=='.'){numofdots++;
                    
                    if (numofdots>1){convertable = FALSE;return; }
                    
                     continue;}
                    if ((e<'0' || e>'9') && e!='.')
                    {
                        convertable = FALSE;
                        return;
                    }
                }
                
            }
            convertable = TRUE;
        }

        void init(){
            bool_index = false;
            str_index = false;
            num_index = false;
            float_index = false;
            bignum_index = false;
            na_index = false;
        }

    public:


        element (bool x):boolValue(x){this->init(); bool_index = true; this->check_invertability(); }

        element (int x):num(x){this->init();num_index = true;this->check_invertability(); }
        element (long x):num(x){this->init();num_index = true;this->check_invertability(); }
        element (unsigned int x):num(x){this->init();num_index = true;this->check_invertability(); }
        element (unsigned long x):bignum(x){this->init();bignum_index = true;this->check_invertability(); }

        element (double x):flo(x){this->init();float_index = true;this->check_invertability();  }
        element (long double x):flo(x){this->init();float_index = true;this->check_invertability(); }
        element (float x):flo(x){this->init();float_index = true;this->check_invertability();  }
        element (NA x = string("NA")):n(x) {this->init(); na_index = true; this->check_invertability(); }
        element (string x):str(x){this->init();str_index = true;this->check_invertability();  }
        element (const char* x):str(x){this->init();str_index = true;this->check_invertability(); }




        element& operator =(int x){num = x;this->init();num_index = true;this->check_invertability();  return *this;}
        element& operator =(long x){num = x;this->init();num_index = true;this->check_invertability(); return *this;}
        element& operator =(unsigned int x){num = x;this->init();num_index = true;this->check_invertability();  return *this;}
        element& operator =(unsigned long x){bignum = x;this->init();bignum_index = true;this->check_invertability();   return *this;}

        element& operator =(double x){flo = x;this->init();float_index = true; this->check_invertability();   return *this;}
        element& operator =(long double x){flo = x;this->init();float_index = true; this->check_invertability();  return *this;}
        element& operator =(float x){flo = x;this->init();float_index = true; this->check_invertability();   return *this;}

        element& operator =(string x){str = x;this->init();str_index = true; this->check_invertability();    return *this;}
        element& operator =(const char* x){str = x;this->init();str_index = true; this->check_invertability();   return *this;}
        element& operator =(bool x){boolValue = x;this->init();bool_index = true; this->check_invertability(); return *this;}
        element& operator = (NA x) {this->init(); na_index = true; this->check_invertability(); return *this;}

        bool operator <(element other){
            if(this->str_index ||
                other.str_index||
                this->bool_index||
                other.bool_index||
                this->na_index||
                other.na_index){return false;}

            return this->verify()<other.verify();
        }

        bool operator >(element other){
            if(this->str_index || other.str_index||this->bool_index||other.bool_index||
                this->na_index||
                other.na_index){return false;}
            return this->verify()>other.verify();
        }
        bool operator >=(element other){
            if(this->str_index || other.str_index||this->bool_index||other.bool_index||
                this->na_index||
                other.na_index){return false;}
            return this->verify()>=other.verify();
        }
        bool operator <=(element other){
            if(this->str_index || other.str_index||this->bool_index||other.bool_index||
                this->na_index||
                other.na_index){return false;}
            return this->verify()<=other.verify();
        }        
        bool operator == (element other){
            if (this->na_index && other.na_index){return true;}
            if (this->str_index && other.str_index){return this->str == other.str;}
            if (this->bool_index&& other.bool_index){return this->boolValue == other.boolValue;}
            return this->verify() == other.verify();
            
        }
        bool operator != (element other){
            if (this->na_index && other.na_index){return false;}
            if (this->str_index && other.str_index){return this->str != other.str;}
            if (this->bool_index&& other.bool_index){return this->boolValue != other.boolValue;}
            return this->verify() != other.verify();
        }
        element operator * (element other){
            element x;
            if (this->na_index || other.na_index){NA d;x=d;return x;}
            if (other.bool_index || this->bool_index){cout<<"not possible to put boolean as an argument"; exit(1);}
            if (this->str_index && other.str_index)
            {
                cout<<"not possible to multiple string with string"; exit(1);
            }
            if (this->str_index){
                if (other.verify() != long(other.verify())){cout<<"not possible to multiple string with float"; exit(1);}
                string stre = this->str,stri = this->str;
                for (int i = 0; i < other.verify()-1; i++)
                {
                    stre+=stri;
                }
                x=stre;
                return x;
            }

            if (other.str_index){
                if (this->verify() != long(this->verify())){cout<<"not possible to multiple string with float"; exit(1);}
                string stre = other.str;
                string stri = other.str;
                for (int i = 0; i < this->verify()-1; i++)
                {
                    stre+=stri;
                }
                x=stre;
                
                return x;
            }
            x=this->verify()*other.verify();
            
            return x;


        }
        void operator *=(element other){
            element x;
            if (this->na_index || other.na_index){NA d;x=d; *this = x; return;}

            if (other.bool_index || other.str_index||this->bool_index)
                {cout << "you have to multiple by numbers" << endl; exit(1);}

            if (this->str_index){
                if (other.verify() != long(other.verify())){cout<<"not possible to multiple string with float"; exit(1);}
                string stre = this->str,stri = this->str;
                for (int i = 0; i < other.verify()-1; i++)
                {
                    stre+=stri;
                }
                this->str = stre;
                return;
                
            }

            x=this->verify()*other.verify();
            *this = x;

            
            
            

        }
        
        element operator/(element other){
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"variable is not a number"<<endl;exit(1);
            }

            element x;
            if (this->na_index || other.na_index){NA d;x=d;return x;}            
            x = this->verify()/other.verify();

            return x;
        }

        void operator/=(element other){
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"variable is not a number"<<endl; exit(1);
            }
            element x;
            if (this->na_index || other.na_index){NA d;x=d; *this = x; return;}
            x = this->verify()/other.verify();
            
            *this = x;
        }

        element operator+(element other){
            element x ;
            if (this->na_index || other.na_index){NA d;x=d;return x;}    
            if (this->bool_index||other.bool_index){
                cout<<"boolean value is not able to add or be added"<<endl;exit(1);
            }
            if (this->str_index && other.str_index)
            {
                x = this->str+other.str;
                return x;
            }
            if (this->str_index || other.str_index)
            {
                cout<<"string and numeric value is not able to add or be added"<<endl;
                exit(1);
            }
            

            x = this->verify()+other.verify();
            return x;
        }

        void operator+=(element other){
            element x;

            if (this->na_index || other.na_index){NA d;x=d; *this = x; return;}
            if (this->bool_index||other.bool_index){
                cout<<"boolean value is not able to add or be added"<<endl;exit(1);
            }
            if (this->str_index && other.str_index)
            {
                x = this->str+other.str;
                *this = x;
                return;
            }
            if (this->str_index || other.str_index)
            {
                cout<<"string and numeric value is not able to add or be added"<<endl;exit(1);
            }
            

            x = this->verify()+other.verify();
            *this = x;
            return ;
        }

        element operator-(element other){
            element x ;
            if (this->na_index || other.na_index){NA d;x=d;return x;}  
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"value has to be numeric"<<endl;exit(1);
            }
            x = this->verify()-other.verify();
            return x;
        }
        void operator-=(element other){
            element x ;
         
            if (this->na_index || other.na_index){NA d;x=d; *this = x; return;}
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"value has to be numeric"<<endl;exit(1);
            }
            x = this->verify()-other.verify();
            *this = x;
        }
        
        element operator %(element other){
            element x ;
            if (this->na_index || other.na_index){NA d;x=d; return x;}  
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"value has to be numeric"<<endl;exit(1);
            }

            if(this->verify()!=long(this->verify())||other.verify()!=long(other.verify())){
                cout<<"modulu cant be made by float"<<endl;exit(1);
            }
            x=long(this->verify())%long(other.verify());

            return x;
        }
        
        void operator %=(element other){
            element x ;
            if (this->na_index || other.na_index){NA d;x=d; *this = x; return;}            
            if (this->bool_index||other.bool_index||this->str_index||other.str_index){
                cout<<"value has to be numeric"<<endl;exit(1);
            }

            if(this->verify()!=long(this->verify())||other.verify()!=long(other.verify())){
                cout<<"modulu cant be made by float"<<endl;exit(1);
            }
            x=long(this->verify())%long(other.verify());

            *this = x;
        }
        
        friend ostream& operator<<(ostream& os, const element& self){
            if(self.num_index){return os << self.num;}
            if(self.bignum_index){return os << self.bignum;}
            if(self.float_index){return os << self.flo;}
            if(self.str_index){return os << self.str;}
            if(self.bool_index){return os << (self.boolValue? "TRUE":"FALSE");}
            

            return os << self.n;

        }

        string etype(){
            if (this->bool_index){return Boolean;}
            if (this->str_index){return STR;}
            if (this->num_index ||this->bignum_index){return INT;}
            if (this->float_index){return Float;}
            return "NA";
        }


        bool is_convertable(){
            return this->convertable;
        }


        void convert_to(string typer){
            if (typer == STR){

                
                if (this->str_index){return;}
                else if (this->num_index){this->str = to_string(this->num);}
                else if (this->float_index){this->str = to_string(this->flo);}
                else if (this->bignum_index){this->str = to_string(this->bignum);}
                else if (this->bool_index){this->str = to_string(this->boolValue);}
                this->init();
                str_index = TRUE;
                return;

            }
            if (this->convertable == FALSE){cout <<"not possible to convert that string to a number" << endl; exit(1);}
           
            if (typer == Float){
                if (this->str_index){this->flo = stold(this->str);}
                
                else if (this->num_index){this->flo = this->num;}
                else if (this->float_index){ return;}
                else if (this->bignum_index){this->flo= this->bignum;}
                else if (this->bool_index){this->flo = this->boolValue;}
                this->init();
                this->float_index = true;
                return;
            }

                       
            if (typer == INT){
                if (this->str_index){this->num = stold(this->str);}
                else if (this->num_index||this->bignum_index){return;}
                else if (this->float_index){ this->num = this->flo;}
                
                else if (this->bool_index){this->num = this->boolValue;}
                this->init();
                
                this->num_index = true;
                return;
            }

            cout << "wrong type entered! not converted" << endl;
        }
};

class series{
    private:
        vector<element> vec;
        

    public:
        series(vector<element> vec1 ={}):vec(vec1) {}   
        



        series& operator=(vector<element> vec1){
            
            vec = vec1;
            return *this;

        }

        series& operator=(vector<string> vec1){
            for (const auto& s : vec1){
                vec.push_back(s);
            }
            return *this;

        }

        void operator=(int f){
            
            for (int i=0; i<this->vec.size(); i++){
                this->vec[i] = f;
            }
            
            
            

        }
        friend ostream& operator<<(ostream& os, const series& self){
            os << "[";
            int i = 0;
            for(const auto& y : self.vec)
            {
                os << y;
                if (i< self.vec.size()-1){
                    os<< ", ";
                }
                i++;
            
            }
            return os<< "]";
        }

        void append(element d){
            this->vec.push_back(d);

        }

        series operator == (element x){
            series t;
            for (int i = 0; i<this->vec.size();i++){
                
                t.append( this->vec[i]==x );
            }
            return t;
        }
        series operator == (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]==value[i]);}
            return ret;

        } 
        
        
        series operator > (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]>value[i]);}
            return ret;

        }      
        series operator > (element x){
            series t;
            for (int i = 0; i<this->vec.size();i++){
                
                t.append( this->vec[i]>x );
            }
            return t;
        }
        
        
        series operator <= (element x){
            series t;
            for (int i = 0; i<this->vec.size();i++){
                
                t.append( this->vec[i]<=x );
            }
            return t;
        }
        series operator <= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]<=value[i]);}
            return ret;

        }        
        
        series operator >= (element x){
            series t;
            for (int i = 0; i<this->vec.size();i++){
                
                t.append( this->vec[i]>=x );
            }
            return t;
        }
        series operator >= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]>=value[i]);}
            return ret;

        }       
        
        series operator < (element x){




            series t;
            for (int i = 0; i<this->vec.size();i++){
                
                t.append( this->vec[i]<x );
            }
            return t;
        }
        series operator < (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]<value[i]);}
            return ret;

        }

        void convert(string typer)
        {

        }
        element& operator [](int t){
            if (t>=this->length()){cout<<"this index is not exists in that series"<<endl;exit(1);}
            return this->vec[t];
        }

        
        series operator [](series t){
            series ret;
            for (int i = 0; i <this->vec.size(); i++){
                if (t[i] == TRUE){ret.append(this->vec[i]);}
            }
            return ret;
        }

        series operator [] (vector<int> ve){
            series ret;
            for (const auto& i : ve){
                ret.append(this->vec[i]);
            }
            return ret;
        }

        series operator &&(series other){
            series tot;
            
            for (int i = 0; i < this->vec.size(); i++){
                
                tot.append((this->vec[i] == TRUE )&& (other.vec[i] == TRUE));
               
                
            }
            return tot;
        }

        series operator ||(series other){
            series tot;
            
            for (int i = 0; i < this->vec.size(); i++){
                
                tot.append((this->vec[i] == TRUE )|| (other.vec[i] == TRUE));
               
                
            }
            return tot;
        }

        void erase_index(int index){
            this->vec.erase(this->vec.begin()+index);
        }

        void insert_index(int index,element value){
            this->vec.insert(this->vec.begin()+index,value);
        }


        series operator+(element value){
            series ret;
            for (int i=0;i<this->vec.size();i++){
                ret.append(this->vec[i]+value);
            }
            return ret;
        }


        series operator + (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]+value[i]);}
            return ret;

        }

        void operator += (element value){
            *this = *this + value;
        }

        void operator += (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]+value[i]);}
            *this =  ret;
            
        }

        series operator -(element value){
            series ret;
            for (int i=0;i<this->vec.size();i++){
                ret.append(this->vec[i]-value);
            }
            return ret;
        }

        series operator - (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]-value[i]);}
            return ret;
            
        }

        void operator -= (element value){
            *this = *this - value;
        }        

        void operator -= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]-value[i]);}
            *this =  ret;
            
        }

        series operator *(element value){
            series ret;
            for (int i=0;i<this->vec.size();i++){
                ret.append(this->vec[i]*value);
            }
            return ret;
        }

        series operator * (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]*value[i]);}
            return ret;
            
        }

        void operator *= (element value){
            *this = *this * value;
        }

        void operator *= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]*value[i]);}
            *this =  ret;
            
        }

        series operator / (element value){
            series ret;
            for (int i=0;i<this->vec.size();i++){
                ret.append(this->vec[i]/value);
            }
            return ret;
        }

        series operator / (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]/value[i]);}
            return ret;
            
        }

        void operator /= (element value){
            *this = *this / value;
        }

        void operator /= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]/value[i]);}
            *this =  ret;
            
        }

        series operator %(element value){
            series ret;
            for (int i=0;i<this->vec.size();i++){
                ret.append(this->vec[i]%value);
            }
            return ret;
        }

        series operator % (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]%value[i]);}
            return ret;
            
        }

        void operator %= (element value){
            *this = *this % value;
        }

        void operator %= (series value){
            series ret;
            if (this->length()!=value.length()){cout<<"sizes are not the same"<<endl; exit(1);}
            for (int i=0; i<value.length();i++){ret.append(this->vec[i]%value[i]);}
            *this =  ret;
            
        }

        void convert_to(string value){
            for (int i=0; i<this->vec.size();i++){
                this->vec[i].convert_to(value);
            }
        }

        void change_to(element e,series f){
            for (int i=0; i<this->length(); i++){
                if (f[i] == TRUE){
                    this->vec[i] = e;

                }
            }
        }

        int length(){
            return this->vec.size();
        }

        element mean(bool na_rm = false){

            element me = 0,g = 0;

            for (int i = 0; i < this->vec.size();i++){
                if (this->vec[i].etype() == "NA" && na_rm == true){g+=1;continue;}
                me+=this->vec[i];
            }
            g-=this->length();
            g*=-1;

            return me/g;
        }

        element max(bool na_rm = false){
            element me = 0;
            if (this->vec.size() == 0){
                return nan("1");
            }
            me = this->vec[0];
            for (int i = 0; i < this->vec.size();i++){
                if (this->vec[i]>me){me = this->vec[i];}
            }
            return me;
            
        }
        element min(bool na_rm = false){
            element me = 0,g=0;
            if (this->vec.size() == 0){
                return nan("1");
            }
            me = this->vec[0];
            for (int i = 0; i < this->vec.size();i++){
                if (this->vec[i]<me){me = this->vec[i];}
            }
            return me;
            
        }        


};

series range(int start = 0,int end = 0,int step = 1){
    series f;
    if (step == 0){return f;}

    for (int i = start ; i < end ; i = i+step){
        f.append(i);
    }
    return f;
}

series linspace(long double start, long double end, int n){
    long double gap = (end - start)/n;
    series f;
    for (int i  = 0;i<n+1 ; i++){
        f.append(start + gap*i);
    }
    return f;
}



class dataframe{
    private:
        map <string,series> dic;
         
        int rows =0;
        vector<string> colnames;
        
        series h;
        void init(){

            colnames = {};
            rows = 0;
            bool x = false;
            for (const auto& i:dic){
                colnames.push_back(i.first);
                h = i.second;
                if(x == true && (h.length()!=rows))
                {cout << "all columns need to be in same length" << endl; exit(1);}
                x=true;
                rows = h.length();
                


            }
            
        }
    public:

        dataframe(map <string,series> dic1 = {}):dic(dic1) {

            this->init();
        }   


        dataframe& operator=(map <string,series> dic1){
            

            
            this ->dic = dic1;
            this->init();

            return *this;
        }



        series& operator[](string e){
            this->init();
            return this->dic[e];
        }

        dataframe operator[](vector<string> e){
            this->init();
            dataframe result;
            map<string,series > f;
            series ser;
            ser = e;
            for (const auto& i : e) {
                if ( find(colnames.begin(),colnames.end(),i)==colnames.end()){
                    cout <<"there isnt a column"<< i<<endl;exit(1);
                }
                f[i] = dic[i];
            }
            result = f;
            return result;
        }

        dataframe operator[](series e){
            dataframe result;
            
            this->init();
            for (int i=0;i<e.length();i++){
                if (e[i] == TRUE)
                {
                    for (const auto& s : this->colnames){
                        
                        result.dic[s].append(this->dic[s][i]);
                    }
                }
                
            }

            return result;
        }

        series size (){
            series si;
            this->init();
            si.append(this->rows);
            si.append(this->colnames.size());
            return si;
        }



        friend ostream& operator<<(ostream& os, const dataframe& self){
            int r = 0;
            series h;
            bool a = false;
            vector <string> cols;
            
            for (const auto& s : self.dic){
                h = s.second;
                if (a && h.length() != r){cout << "not all columns ar on same length" << endl; exit(1);}
                r = h.length();
                os<< s.first << "\t";
            }
            os<< endl;
            
            for (int i=0;i<r;i++){
                for (const auto& s :self.dic){
                    h = s.second;
                    os << h[i]<<"\t\t";
                }
                os<< endl;
            }


            return os;
        }






};


int summer(int a=2,int b=5,int c = 3){
    return a+b+c;
}

class table{
    private:
        vector<series> vec;
    public:

        table(vector<vector<element>> vec1={}){
            series g;
            for (int i=0; i<vec1.size();i++){
                g=vec1[i];
                vec.push_back(g);
            }
        }

        table(vector<series> vec1):vec(vec1){
            
            }

        table& operator = (vector<vector<element>> vec1){
            series g;
            for (int i=0; i<vec1.size();i++){
                g=vec1[i];
                vec.push_back(g);
            }
            return *this;
        }


        table& operator = (vector<series> vec1){
            vec = vec1;
            return *this;
        }

        friend ostream& operator<<(ostream& os, const table& self){
            os << "["<<endl;
            int i  = 0;
            for (const auto& f:self.vec){
                os<<f;
                i++;
                if (i<self.vec.size()){os<<", ";}
                
                os<<endl;

            }
            os << "]";
            return os;
        }    
        
};

int main()
{

series f,g;

vector<element> po = {1,2,3,4,5};


f = {1,2,3,9,5,6};
g = {3,2,4,53,6,7};
dataframe y;
table d;
d={{1,2,3},{4,5,6}};
cout<<d<<endl;


    
}