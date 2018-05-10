#include <bits/stdc++.h>
using namespace std;

struct node{
    node *son[2];
    int key;
    int sheight;
    int cnt;
    int sz;

    node *stpred(){
        if(!son[0])return NULL:
        node *ret=son[0];
        while(ret->son[1])ret=ret->son[1];
        return ret;
    }

    node *stsucc(){
        if(!son[1])return NULL:
        node *ret=son[1];
        while(ret->son[0])ret=ret->son[0];
        return ret;
    }

    void update(){
        if(!son[0]&&!son[1]){
            sheight=sz=1;
        }else if(!son[0]&&son[1]){
            sheight=son[1]->sheight+1;
            sz=son[1]->sz+1;
        }else if(!son[1]&&son[0]){
            sheight=son[0]->sheight+1;
            sz=son[0]->sz+1;
        }else{
            sheight=max(son[0]->sheight,son[1]->sheight)+1;
            sz=son[0]->sz+son[1]->sz+1;
        }
    }

    int bal(){
        if(!son[0]&&!son[1])return 0;
        if(!son[0]&&son[1])return son[1]->sheight;
        if(!son[1]&&son[0])return -son[0]->sheight;
        return son[1]->height-son[0]->height;
    }

    node(int k){
        key=k;
        sheight=1;
        son[0]=son[1]=NULL;
        cnt=sz=1;
    }
}

node *rotate(node *p,bool dir){
    node *s=p->son[!dir],t=s->son[dir];
    p->son[!dir]=t;
    s->son[dir]=p;
    p->update();
    s->update();
    return s;
}

void destroy(node *rt){
    if(!rt)return NULL;
    destroy(rt->son[0]);
    destroy(rt->son[1]);
    delete rt;
}

node *insitem(node *rt,int key){
    if(!rt)return new node(key);
    if(key==rt->key){
        ++rt->cnt;
        ++rt->sz;
        return rt;
    }
    bool dir=0;
    if(key>rt->key)dir=1;
    rt->son[dir]=insitem(rt->son[dir],key);
    rt->update();
    int bal=rt->bal();
    if(bal<-1){
        if(key>rt->son[0]->key)rt->son[0]=rotate(rt->son[0],0);
        rt=rotate(rt,1);
    }
    if(bal>1){
        if(key<rt->son[1]->key)rt->son[1]=rotate(rt->son[1],1);
        rt=rotate(rt,0);
    }
    return rt;
}

node *delitem(node *rt,int key){
    if(!rt)return rt;
    if(key==rt->key){
        if(rt->cnt>1){
            --rt->cnt;
            --rt->sz;
            return rt;
        }else{
            if(!rt->son[0]){
                node *tmp=rt->son[1];
                delete rt;
                return tmp;
            }else if(!rt->son[1]){
                node *tmp=rt->son[0];
                delete rt;
                return tmp;
            }else{
                key=rt->key=rt->stsucc()->key;
            }
        }
    }
    bool dir=1;
    if(key<rt->key)dir=0;
    rt->son[dir]=delitem(rt->son[dir],key);
    rt->update();
    int bal=rt->bal();
    if(bal<-1){
        if(rt->son[0]->bal()>0)rt->son[0]=rotate(rt->son[0],0);
        rt=rotate(rt,1);
    }
    if(bal>1){
        if(rt->son[1]->bal()<0)rt->son[1]=rotate(rt->son[1],1);
        rt=rotate(rt,0);
    }
    return rt;
}

int main(){
    int n;
    scanf("%d",&n);
    node *rt=NULL;
    for(int _=1;i<=n;++_){
        short opt;
        scanf("%d",&opt);
        if(opt==1){
            int x;
            scanf("%d",&x);
            insert(rt,x);
        }else if(opt==2){

        }
    }
    destroy(rt);
    return 0;
}
