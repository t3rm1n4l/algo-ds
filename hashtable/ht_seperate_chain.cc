#include <iostream>
#include <sstream>

using namespace std;


#define DEFAULT_BUCKETS 200000

class Value {
    string key;
    string value;
    Value *next;
public:
    Value(string k, string v) {
        key = k;
        value = v;
        next = NULL;
    }

    Value(const Value &v, Value *n = NULL) {
        key = v.key;
        value = v.value;
        next = n;
    }

    string getKey() const {
        return key;
    }

    string getValue() const {
        return value;
    }

    friend class HashTable;
};

class HashTable {
    uint64_t buckets;
    Value **vals;
    uint64_t sz;
    uint64_t resized;

    uint64_t hash(const string &key) {
        const char *s = key.c_str();
        uint64_t h = 0;

        for (size_t i=0; i<key.length(); i++) {
            h = 31*h + s[i];
        }

        return h % buckets;
    }
public:
    HashTable() {
        buckets = DEFAULT_BUCKETS;
        resized = sz = 0;
        vals = new Value*[buckets];
        for (uint64_t i=0; i < buckets; i++) {
            vals[i] = NULL;
        }
    }

    ~HashTable() {
        for (uint64_t i=0; i < buckets; i++) {
            Value *v, *t;
            v = vals[i];
            while (v) {
                t = v->next;
                delete v;
                v = t;
            }
        }

        delete [] vals;
    }

    void put(Value &itm) {
        uint64_t hashcode = hash(itm.key);
        Value *val = new Value(itm, vals[hashcode]);
        vals[hashcode] = val;
        sz++;
        resize();
    }

    bool get(const string &key, Value &itm) {
        uint64_t hashcode = hash(key);
        Value *vb = vals[hashcode];
        if (vb) {
            while (vb != NULL) {
                if (vb->key == key) {
                    Value v(vb->key, vb->value);
                    itm = v;
                    return true;
                }

                vb = vb->next;
            }
        }

        return false;
    }

    bool del(const string &key) {
        uint64_t hashcode = hash(key);
        Value *vb, *prev;
        vb = prev = vals[hashcode];

        if (vb) {
            while (vb != NULL) {
                if (vb->key == key) {
                    if (prev == vb) {
                        vals[hashcode] = vb->next;
                    } else {
                        prev->next = prev->next->next;
                    }

                    sz--;
                    resize();
                    return true;
                }
                prev = vb;
                vb = vb->next;
            }
        }

        return false;
    }

    uint64_t size() const {
        return sz;
    }

    void resize() {
        uint64_t newsize = DEFAULT_BUCKETS;
        if (sz > DEFAULT_BUCKETS) {
            newsize = buckets;
            if (sz > newsize/2) {
                newsize = newsize*2;
            }
            if (sz < newsize/4) {
                newsize = newsize/2;
                if (newsize < DEFAULT_BUCKETS){
                    newsize = DEFAULT_BUCKETS;
                }
            }
        }

        if (newsize != buckets) {
            uint64_t hashcode;
            Value **nwvals = new Value*[newsize];

            uint64_t oldbuckets = buckets;
            buckets = newsize;

            for (uint64_t i=0; i < buckets; i++) {
                nwvals[i] = NULL;
            }

            for (uint64_t i=0; i < oldbuckets; i++) {
                while (vals[i]) {
                    hashcode = hash(vals[i]->key);
                    Value *curr = vals[i];
                    vals[i] = curr->next;
                    curr->next = nwvals[hashcode];
                    nwvals[hashcode] = curr;

                }
            }

            delete [] vals;
            vals = nwvals;
            resized++;
        }
    }

    uint64_t resizes() const {
        return resized;
    }
};

int main() {
    HashTable h;
    Value v1("k1", "v1");
    Value v2("k2", "v1");
    Value v3("k3", "v1");
    h.put(v1);
    h.put(v2);
    h.put(v3);

    cout<<"Size = "<<h.size()<<endl;
    cout<<h.get("k1", v3)<<endl;
    cout<<v3.getKey()<<" = "<<v3.getValue()<<endl;
    h.del("k1");
    cout<<h.get("k1", v3)<<endl;

    for (size_t i=0; i<1500000; i++) {
        stringstream ss;
        ss<<"key-"<<i;
        Value v(ss.str(), ss.str());
        h.put(v);
    }

    cout<<"Resizes = "<<h.resizes()<<endl;
    h.get("key-9", v3);
    cout<<v3.getKey()<<" = "<<v3.getValue()<<endl;


}

