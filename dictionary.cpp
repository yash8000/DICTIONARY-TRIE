#include <bits/stdc++.h>
#include <fstream>
using namespace std;

map<char,int> mchar;
map<string,int> mpron;

struct Word{
    string word;
    string pos;
    string meaning;
};

struct pronWord{
    string word;
    vector<string> v;
};

struct DictNode{
    DictNode* link[40];
    
    vector<Word> word;
    DictNode(){
        for(int i=0;i<40;i++)link[i]=NULL;
        
    }

};

struct pronNode{
    pronNode * link[85];
    int cnt;
    vector<string>v;
    pronNode(){
        for(int i=0;i<85;i++){
            link[i]=NULL;
        }
        cnt=0;
    }
};

struct wordPronNode{
    wordPronNode * link[40];
    vector<vector<string>>v;
    wordPronNode(){
        for(int i=0;i<40;i++){
            link[i]=NULL;
        }
    }
};

class DictTrie{
    public:
        DictNode* root;

        void Build(){
            fstream dict;
            dict.open("./meanings/dictionary.csv");
            if(!dict.is_open()){
                cout << "FILE NOT FOUND" << endl;
                return;
            }
            string line;
            getline(dict,line);
            while(getline(dict,line)){
                // cout << line << endl;
                Word w;
                string word="",meaning="",pos="";
                int f=0;
                for(char c:line){
                    if(f==0){
                        if(c==','){
                            f=1;
                            continue;
                        }
                        if(c>='A' && c<='Z')c=c-'A'+'a';
                        word+=c;
                    }
                    else if(f==1){
                        if(c==','){
                            f=2;
                            continue;
                        }
                        if(c=='\"')continue;
                        pos+=c;
                    }
                    else{
                        meaning+=c;
                    }
                }
                    w.word=word;
                    w.pos=pos;
                    w.meaning=meaning;
            // cout << meaning << endl;
                    AddWord(w);
                    // cout << word << endl;
            }
        }

        void AddWord(Word w){
            DictNode* cur=root;
            for(char c:w.word){
                // int x=c;
                if(cur->link[mchar[c]]==NULL){
                    DictNode* nxt=new DictNode;
                    cur->link[mchar[c]]=nxt;
                }
                cur=cur->link[mchar[c]];
                // cur->cnt++;
            }
                // cout << w.word.size() << endl;
            cur->word.push_back(w);
        }

        vector<Word> Find(string s){
            DictNode* cur=root;
            for(char c:s){
                if(mchar.count(c)==0){
                    vector<Word> v;
                    return v;
                }
                if(cur->link[mchar[c]]==NULL){
                    vector<Word>v;
                    return v;
                }
                cur=cur->link[mchar[c]];
            }
            return cur->word;
        }


};

class pronTrie{
    public:
        pronNode* root;
        wordPronNode* root2;
        void Build(){
            fstream pro;
            pro.open("./pronounciations/cmudict.dict");
            if(!pro.is_open()){
                cout << "FILE NOT FOUND" << endl;
                return;
            }
            string line;
            while(getline(pro,line)){
                int f=0;
                string word="",s="";
                vector<string> v;
                for(char c:line){
                    if(f==0){
                        if(c=='('){
                            f=1;
                            continue;
                        }
                        if(c==' '){
                            f=2;
                            continue;
                        }
                        word+=c;
                    }
                    if(f==1){
                        if(c==' '){
                            f=2;
                            continue;
                        }
                    }
                    if(f==2){
                        if(c==' '){
                            v.push_back(s);
                            s="";
                            continue;
                        }
                        s+=c;
                    }
                }
                v.push_back(s);
                pronWord w;
                w.word=word;
                w.v=v;
                // cout << word << endl;
                AddWord(w);
            }
        }

        void AddWord(pronWord w){
            string word = w.word;
            pronNode* cur=root;
            int sz=w.v.size();
            for(int i=sz-1;i>=0;i--){
                string s=w.v[i];
                if(cur->link[mpron[s]]==NULL){
                    pronNode* nxt=new pronNode;
                    cur->link[mpron[s]]=nxt;
                }
                cur=cur->link[mpron[s]];
                cur->cnt++;
                cur->v.push_back(w.word);
            }
            // cur->v.push_back(w);

            wordPronNode * cur2=root2;
            for(char c:word){
                if(c=='(')break;
                if(cur2->link[mchar[c]]==NULL){
                    wordPronNode* nxt=new wordPronNode;
                    cur2->link[mchar[c]]=nxt;
                }
                cur2=cur2->link[mchar[c]];
                
            }
            cur2->v.push_back(w.v);

        }

        vector<vector<string>> findPron(string s){
            wordPronNode *cur=root2;
            for(char c:s){
                if(mchar.count(c)==0){
                    vector<vector<string>> v;
                    return v;
                }
                if(cur->link[mchar[c]]==NULL){
                    vector<vector<string>> v;
                    return v;
                }
                cur=cur->link[mchar[c]];
            }
            return cur->v;
        }

        vector<string> findRhyme(vector<string> v){
            int sz=v.size();
            pronNode* cur=root;
            vector<string> ans;
            for(int i=sz-1;i>=0;i--){
                cur=cur->link[mpron[v[i]]];
                if(cur->cnt<10)break;
                ans=cur->v;
            }
            return ans;
        }

};


int main(){
    for(char c='a';c<='z';c++){
        mchar[c]=c-'a';
    }
    mchar[' ']=26;
    mchar['-']=27;
    mchar['_']=28;
    for(int i=0;i<10;i++){
        mchar['0'+i]=29+i;
    }

    fstream symb;
    symb.open("./pronounciations/cmudict.symbols");
    string s;
    int i=0;
    while(getline(symb,s)){
        // cout << s << endl;
        mpron[s]=i;
        i++;
    }
    




    
    DictNode* rt= new DictNode;
    DictTrie* t=new DictTrie;
    t->root=rt;
    t->Build();

    wordPronNode* rtwp=new wordPronNode;
    pronNode* rtp=new pronNode;
    pronTrie* t2=new pronTrie;
    t2->root=rtp;
    t2->root2=rtwp;
    t2->Build();
    cout << endl;
    while(1){
        cout << "Choose an option:\n";
        cout << "1: Find meaning and part of speech of a word\n";
        cout << "2: Find a list of words that rhyme with the given word\n";
        cout << "Any other Number: Exit\n";
        cout << "Enter Number: ";
        
        int x;
        cin >> x;
        if(x==1){
            cout << endl;
            cout << "Enter Word to find meaning and part of speech: ";
            string s;
            cin >> s;
            for(int i=0;i<s.size();i++){
                if(s[i]>='A' && s[i]<='Z')s[i]=s[i]-'A'+'a';
            }
            vector<Word> ans;
            ans=t->Find(s);
            if(ans.size()==0){
                cout << "Word not Found." << endl;
                continue;
            }
            cout << "\tWord" << "\t" << "POS\t\t" << "Meaning\n";
            for(int i=0;i<ans.size();i++){
                cout << i+1 << ".\t" << ans[i].word << '\t' << ans[i].pos << '\t' << ans[i].meaning << endl;
            }
            cout << endl ;

        }
        else if(x==2){
            cout << endl;
            cout << "Enter Word to find Rhyming Words: ";
            string s;
            cin >> s;
            for(int i=0;i<s.size();i++){
                if(s[i]>='A' && s[i]<='Z')s[i]=s[i]-'A'+'a';
            }
            vector<vector<string>> v=t2->findPron(s);
            if(v.empty()){
                cout << "Word Not Found" << endl;
                continue;
            }
            int x=1;
            for(vector<string> vv:v){
                vector<string> ans=t2->findRhyme(vv);
                cout << x <<". ";
                x++;
                int maxSize=50;
                int vecSize=ans.size();
                for(int i=0;i<min(maxSize,vecSize);i++){
                    if(ans[i]==s)continue;
                    cout << ans[i] << ' ';
                }
                cout << endl;

            }
            cout << endl;
        }
        else{
            cout << endl;
            return 0;
        }
    }



    return 0;
}