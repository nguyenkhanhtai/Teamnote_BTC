struct Node{    
    int l, r, ll, rr; //[l, r] are the ranges | ll, rr: left, right children
};
struct sparseIT{
    /*A sample sparse IT with following operations:
     - Get the number of elements in a range. 
     - Get the sum of elements in a range.
     Lazy operations could be implemented as well
    */
      vector<Node> st;
      int rt = 0;
      int getInfo(int nn){ 
          //Return Some kind of info
      }
      void update(int nn){
           //Update the node nn.
      }
      sparseIT(int _l = 0, int _r = 0){
           rt = 0;
           st.pb(Node(_l, _r));
      }
      void updatePos(int nn, int pos, int value){
           if (st[nn].l == st[nn].r){

               //Change update position
               return;
           }
           int mid = (st[nn].l + st[nn].r) >> 1;
           if (pos <= mid){
               if (st[nn].ll == -1) { //init
                   st[nn].ll = st.size();
                   st.pb(Node(st[nn].l, mid));   
               }
               updatePos(st[nn].ll, pos, value);
           }
           else{
               if (st[nn].rr == -1) { //init
                   st[nn].rr = st.size();
                   st.pb(Node(mid + 1, st[nn].r));   
               }
               updatePos(st[nn].rr, pos, value);
           }
           update(nn);
      }
      int getRange(int nn, int u, int v){
         if (u > v) return 0;
         if (nn == -1) return 0;
         if (st[nn].l >= u and st[nn].r <= v){
             //return infos here
         }
         if (st[nn].l > v or st[nn].r < u) {
             return 0;
         }
         return getSize(st[nn].ll, u, v) +
                getSize(st[nn].rr, u, v);
      }
};