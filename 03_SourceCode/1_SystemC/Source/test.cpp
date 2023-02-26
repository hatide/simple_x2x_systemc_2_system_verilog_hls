class test
{
private:
    /* data */
public:
    test(/* args */);
    ~test();
    static int var_i; // static region
    int var_a;
    // extern  ssss;// -> use inside diffence file
    virtual void test_A();
    virtual void test_B() = 0;
};

int test::var_i = 0;

test::test(/* args */)
{
}

test::~test()
{
}

void test::test_A(){

}

class b:public test
{
private:
    /* data */
public:
    void test_A();
    void test_B();
    b(/* args */);
    ~b();

};

void b::test_A(){


}

void b::test_B(){
    

}

b::b(/* args */)
{
}

b::~b()
{
}

