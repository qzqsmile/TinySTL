#ifndef PAIR_H  
#define PAIR_H  
  
#define __STL_MEMBER_TEMPLATES

template <class T1, class T2>  
struct pair {  
  typedef T1 first_type;  
  typedef T2 second_type;  
//û���÷����޶���������structĬ����public  
  T1 first;     // ע�⣬���� public  
  T2 second;        // ע�⣬���� public  
    
  //Ĭ�Ϲ��캯��������ģ�������Ĭ�Ϲ��캯��  
  //���pair��Ԫ��Ҫ��Ĭ�Ϲ��캯��  
  pair() : first(T1()), second(T2()) {}  
  pair(const T1& a, const T2& b) : first(a), second(b) {}  
  
#ifdef __STL_MEMBER_TEMPLATES  
  //��һ��pair��ʼ����һ��pair�����Ϳ��Բ�ͬ��������ת���ͺá�  
  template <class U1, class U2>  
  pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}  
#endif  
};  
//����pair��ȣ���ζ�������е�����Ԫ�ض���ȡ�  
template <class T1, class T2>  
inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {   
  return x.first == y.first && x.second == y.second;   
}  
  
template <class T1, class T2>  
inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y) {   
  return x.first < y.first || (!(y.first < x.first) && x.second < y.second);   
  // x�ĵ�һԪ��С��y�ĵ�һԪ�أ���x�ĵ�һԪ�ز�����y�ĵ�һԪ�ض�  
  // x�ĵڶ�Ԫ��С��y�ĵڶ�Ԫ�أ���ҕ��xС�y��  
}  
  
//����������ֵ������һ��pair  
template <class T1, class T2>  
inline pair<T1, T2> make_pair(const T1& x, const T2& y) {  
  return pair<T1, T2>(x, y);  
}  
  
#endif /* __SGI_STL_INTERNAL_PAIR_H */  