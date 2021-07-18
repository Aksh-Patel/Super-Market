#include<bits/stdc++.h>
using namespace std;
/*
    -> I had used hashing with chaining data structure.
    -> In which linked_list class contains all the functions of a singly linked list associate with each table bucket.
    -> Table is the array of different linked list as in hashing with chaining data structure.
    -> Hash table of product items is stored in Inventory class.
    -> Hash table of customer item is stored in Customer class.
    -> Billing class performs same work as done by billing counter.
    -> Manager class uploads product data and also modify it.
*/
struct node
{
     long int id;
     string name;
     float rate;
     int quantity;
     float points;
     node *next;
};
//----------------------------------------------------------------------------------------------------------
class linked_list
{
    private:
     node *head,*tail;
    public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
    node* gethead()
    {
        return head;
    }

    void linkedList_addProduct(long int id,string name,float rate,int quantity)//adds new product item 
    {
         node *tmp1 = new node;
         tmp1->id = id;
         tmp1->name =name;
         tmp1->rate = rate;
         tmp1->quantity=quantity;
         tmp1->next = NULL;

         if(head == NULL)
         {
            head = tmp1;
            tail = tmp1;
         }
         else
         {
            tail->next=tmp1;
            tail=tail->next;
         }

     }
    void linkedList_addCustomer(long int id,string name,float points)      // adds new customer
    {
         node *tmp1 = new node;
         tmp1->id = id;
         tmp1->name =name;
         tmp1->points = points;
         tmp1->next = NULL;

         if(head == NULL)
         {
             head = tmp1;
             tail = tmp1;
         }
         else
         {
            tail->next=tmp1;
            tail=tail->next;
         }
     }

    void linkedList_deleteProduct(long int id)                             // delete any product with given product id
    {
        node *tmp;
        tmp=head;
        node *prev;
        prev=tmp;
        while(!(tmp->id == id))
        {
            prev=tmp;
            tmp=tmp->next;
        }
        if(tmp==head)
        {
            head=tmp->next;
            tmp->next=NULL;
            delete tmp;
        }
        else
        {
            prev->next=tmp->next;
            delete tmp;
        }

    }

    void linkedList_updateProduct(long int id,string name,float rate,int quantity)    // update product information
    {
        node *tmp;
        tmp=head;
        while(!(tmp->id == id))
        {
            tmp=tmp->next;
        }
        tmp->id=id;
        tmp->name=name;
        tmp->rate=rate;
        tmp->quantity=quantity;
    }
    void linkedList_updateCustomer(long int id,string name,float points)         // update customer information
    {
        node *tmp;
        tmp=head;
        while(!(tmp->id == id))
        {
            tmp=tmp->next;
        }
        tmp->id=id;
        tmp->name=name;
        tmp->points=points;
    }

    void linkedList_displayProduct()                                  // display product information
    {
         node *tmp;
         tmp = head;
         while (tmp != NULL)
         {
             cout << tmp->id<<" "<<tmp->name<<" "<<tmp->rate<<" "<<tmp->quantity<< endl;
             tmp = tmp->next;
         }
         cout << "NULL\n\n" << endl;
     }
    void linkedList_displayCustomer()                                  // display customer information
    {
         node *tmp;
         tmp = head;
         while (tmp != NULL)
         {
             cout <<tmp->id<<" "<<tmp->name<<" "<<tmp->points<< endl;
             tmp = tmp->next;
         }
         cout << "NULL\n\n" << endl;
     }

    void linkedList_updateStock(long int id,int quantity)                  // update stock of products
    {
        node *tmp;
        tmp=head;
        while(tmp->id != id)
        {
            tmp = tmp->next;
        }
        tmp->quantity=tmp->quantity - quantity;
    }

    string linkedList_getName(long int id)                              // returns name of customer
    {
        node *tmp;
        tmp=head;
        while(tmp->id != id)
        {
            tmp = tmp->next;
        }
        return tmp->name;
    }
    float linkedList_getRate(long int id,long int quantity)                    // returns rate of product
    {
        node *tmp;
        tmp=head;
        while(tmp->id != id)
            tmp = tmp->next;
        return tmp->rate;
    }

    void linkedList_updateCustomerPoints(long int id,float points)        //  update customer points after payment
    {
        node *tmp;
        tmp=head;
        while(tmp!=NULL && tmp->id != id)
            tmp = tmp->next;
        tmp->points=tmp->points + points;
    }
    void linkedList_checkCustomerId(long int customerId)
    {
        node *tmp;
        tmp=head;
        while(tmp!=NULL && tmp->id != customerId)
            tmp = tmp->next;
        if(tmp==NULL)
            linkedList_addCustomer(customerId,to_string(customerId%10),0);
    }
};


//-------------------------------------------------------------------------------------------------------------------
class Customer:public linked_list
{
    private:
    int bucket=13;
    linked_list *table=new linked_list[13];

    void addCustomerData(long int id,string name,float points)
    {
        int index=id%bucket;
        table[index].linkedList_addCustomer(id,name,points);
    }
    void deleteCustomerData(long int id)
    {
        int index=id%bucket;
        table[index].linkedList_deleteProduct(id);
    }
    void updateCustomerData(long int id,string name,float points)
    {
        int index=id%bucket;
        table[index].linkedList_updateCustomer(id,name,points);
    }
   void getCustomerInfo()
    {
        for (int i = 0; i < bucket; i++)
        {
            cout << i<<endl;
            table[i].linkedList_displayCustomer();
        }
    }
    void updateCustomerPoints(long int id,float points)
    {
        int index=id%bucket;
        table[index].linkedList_updateCustomerPoints(id,points);
    }
    void checkCustomer(long int id)
    {
        int index=id%bucket;
        table[index].linkedList_checkCustomerId(id);
        /*if(flag==1)
        {
            table[index].linkedList_addCustomer(id,name,points);
        }*/
    }
    friend class Manager;
    friend class Billing;

};


//-------------------------------------------------------------------------------------------------------------------
class Inventory;    //just declaration


//-------------------------------------------------------------------------------------------------------------------
class Billing
{
    public:

    void addCustomer(Customer C,long int id,string name,float points)
    {
        C.addCustomerData(id,name,points);
    }
    void deleteCustomer(Customer C,long int id)
    {
        C.deleteCustomerData(id);
    }
    void updateCustomer(Customer C,long int id,string name,float points)
    {
        C.updateCustomerData(id,name,points);
    }
    void displayCustomer(Customer C)
    {
        C.getCustomerInfo();
    }
    void updateCustomerPoint(Customer C,long int id,float total)
    {
        C.updateCustomerPoints(id,total);
    }
    void checkCustomerId(Customer C,long int customerId)
    {
        C.checkCustomer(customerId);
    }
    //---------------Below functions are of Inventory class used as friend function---------------------------

    void updateProductStock(Inventory I,long int id,int quantity);
    void getProductInfo(Inventory I);
    string getProductName(Inventory I,long int id);
    float getProductRate(Inventory I,long int id,long int quantity);
    //--------------------------------------------------------------------------------------------
    void make_payment(Inventory I,Customer C,Billing B,long int id);

};


//----------------------------------------------------------------------------------------------------------------------
class Inventory:public linked_list
{
    private:
    int bucket=13;                                          // length of array
    linked_list *table=new linked_list[13];                 // making a singly linked list at every array index

    void addProductItem(long int id,string name,float rate,int quantity)
    {
        int index=id%bucket;
        table[index].linkedList_addProduct(id,name,rate,quantity);
    }
    void deleteProductItem(long int id)
    {
        int index=id%bucket;
        table[index].linkedList_deleteProduct(id);
    }
    void updateProductItem(long int id,string name,float rate,int quantity)
    {
         int index=id%bucket;
        table[index].linkedList_updateProduct(id,name,rate,quantity);
    }
    void getProductItemInfo()
    {
        for (int i = 0; i < bucket; i++)
        {
            cout << i<<endl;
            table[i].linkedList_displayProduct();
        }
    }

    //----------------------------Bellow functions are for Billing class -------------------------

    friend void Billing::updateProductStock(Inventory I,long int id,int quantity);
    friend void Billing::getProductInfo(Inventory I);
    friend string Billing::getProductName(Inventory I,long int id);
    friend float Billing::getProductRate(Inventory I,long int id,long int quantity);

    friend class Manager;   // Making Manager as a friend of Inventory.
};


//----------------------------------------------------------------------------------------------------------------------
class Manager
{
    public:

    void addProduct(Inventory I,long int id, string name, float rate,int quantity)
    {
        I.addProductItem(id,name,rate,quantity);
    }
    void deleteProduct(Inventory I,long int id)
    {
        I.deleteProductItem(id);
    }
    void updateProduct(Inventory I,long int id,string name,float rate,int quantity)
    {
        I.updateProductItem(id,name,rate,quantity);
    }
    void displayProduct(Inventory I)
    {
        I.getProductItemInfo();
    }

};


//--------------------Some functions of Inventory class used by Billing object--------------------------------

void Billing::updateProductStock(Inventory I,long int id,int quantity)
    {
        int index=id%I.bucket;
        I.table[index].linkedList_updateStock(id,quantity);
    }
void Billing::getProductInfo(Inventory I)
    {
        for (int i = 0; i < I.bucket; i++)
        {
            cout << i<<endl;
            I.table[i].linkedList_displayProduct();
        }
    }
string Billing::getProductName(Inventory I,long int id)
    {
        int index=id%I.bucket;
       return I.table[index].linkedList_getName(id);
    }
float Billing::getProductRate(Inventory I,long int id,long int quantity)
    {
        int index=id%I.bucket;
       return I.table[index].linkedList_getRate(id,quantity);
    }

//---------------------------------------------------------------------------------------------------

void Billing::make_payment(Inventory I,Customer C,Billing B,long int id)
    {
        int noOfProducts,total=0;
        cin>>noOfProducts;
        long int a[2*noOfProducts];
        cout<<"CustomerId: "<<id<<endl;
        cout<<"ProductID\tName\tRate\tQuantity   Amount\n";
        for(int i=0;i<2*noOfProducts;i=i+2)
        {
            cin>>a[i];      // product id
            cin>>a[i+1];    // product quantity

            string s = B.getProductName(I,a[i]);
            float rate=B.getProductRate(I,a[i],a[i+1]);
            float amount=rate*a[i+1];
            total=total+amount;

            cout<<a[i]<<"\t"<<s<<"\t"<<rate<<"\t"<<a[i+1]<<"\t    "<<amount<<endl;

            B.updateProductStock(I,a[i],a[i+1]);                  // updating product stock after payment
        }
        cout<<"\t\t\t      Total Amount: "<<total<<endl;

        B.updateCustomerPoint(C,id,total);                     // updating customer point after payment

    }





int main()
{
    long long INVENTORY_DATASET[100][4] = {
    {111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},                            {111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},                        {111100000009,9,180,20},{111100000010,10,190,20},
    {111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},                        {111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},                    {111100000019,19,280,20},{111100000020,20,290,20},
    {111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},                        {111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},                        {111100000029,29,380,20},{111100000030,30,390,20},
    {111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},                    {111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},                        {111100000039,39,480,20},{111100000040,40,490,20},
    {111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},                    {111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},                        {111100000049,49,580,20},{222200001111,50,590,20},
    {222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},                    {222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},                        {222200001138,59,680,20},{222200001141,60,690,20},
    {222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},                    {222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},                        {222200001168,69,780,20},{222200001171,70,790,20},
    {222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},                    {222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},            {222200001198,79,880,20},{222200001201,80,890,20},
    {222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
    {222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
    };
    long long CUSTOMER_DATASET[100][3] = {
    {9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
    {9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
    {9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
    {9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
    {9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
    {9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
    {9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
    {9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
    {9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
    {9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
    };

    //------------------------Uploading Inventory data by manager object---------------------------
    Inventory I;
    Manager M;
    for(int i=0;i<100;i++)
    {
        M.addProduct(I,INVENTORY_DATASET[i][0],to_string(INVENTORY_DATASET[i][1]),INVENTORY_DATASET[i][2],INVENTORY_DATASET[i][3]);
    }   

    //-----------------------Uploading Customer data by Billing object----------------------------
    Customer C;
    Billing B;
    for(int i=0;i<100;i++)
    {
        B.addCustomer(C,CUSTOMER_DATASET[i][0],to_string(CUSTOMER_DATASET[i][1]),CUSTOMER_DATASET[i][2]);
    }

    //---------------------- Now shopping episode begins -------------------------------------

    int noOfCustomers;
    cin>>noOfCustomers;
    for(int i=0;i<noOfCustomers;i++)
    {

        long int customerId;                                       //customer id
        cin>>customerId;
        B.checkCustomerId(C,customerId);                      // assign customerId for a new customer
        cout<<"\n\nTransaction ID: ABCDEF"<<i+1<<endl;      //transaction id starts from ABCDEF1
        B.make_payment(I,C,B,customerId);                          //calling episode function to make payment bill

    }
        //M.displayProduct(I);                              // quantity is updated after every payment of bill
        //B.displayCustomer(C);                             // customer points are updated after every payment

    //--------------------------- Shopping Episode completes ---------------------------------------


    //-----Below functions are just for checking purpose remove any '//' to make use of it---------

    //M.displayProduct(I);
    //M.deleteProduct(I,111100000001);
    //M.displayProduct(I);
    //M.updateProduct(I,222200001186,to_string(99),(float)999,99);
    //M.displayProduct(I);

    //B.displayCustomer(C);
    //B.deleteCustomer(C,9400000021);
    //B.displayCustomer(C);
    //B.updateCustomer(C,9400000067,to_string(99),(float)999);
    //B.displayCustomer(C);
    //B.updateProductStock(I,111100000010,99999);
    //B.getProductInfo(I);

    //-------------------------------------------------------------------------------------------

}
// end of main





/*Try this in the input for one customer ---------------------

1                   //total no of customers purchasing
9400000011          //Customer id of 1st customer
3                   //no. of products bought by 1st customer with above customerid
111100000011        //Product 1 Id
3                   //Product 1 Quantity purchased
222200001114        //Product 2 Id
1                   //Product 2 Quantity purchased
222200001234        //Product 3 Id
2                   //Product 3 Quantity purchased

-----------Or Copy this and paste in custom input for 2 customers----------------------
2
9400000011
3
111100000011
3
222200001114
1
222200001234
2
9400000051
5
111100000045
11
111100000043
11
222200001132
9
222200001252
11
222200001261
15
-----------------------------------------------------------------------
*/
