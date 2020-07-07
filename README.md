# SW-Training  


## Site  
<a href='https://boj.kr'>Baekjoon Online Judge</a><br>
<a href='https://www.swexpertacademy.com'>Samsung SWEA</a><br>
<a href='https://algospot.com'>ALGOSPOT</a><br>
<a href='https://leetcode.com/'>LeetCode</a><br>

## Python  

### 자료구조의 Empty 판단  

str, list, set, tuple, dict 등 자료구조의 Empty 판단은 bool()을 통해 하거나 조건문에는 해당 객체를 바로 써주면 됩니다  

```
if items:
    print("items is not Empty")
elif not items:
    print("items is Empty")
```  

```
if bool(items):
    print("items is not Empty")
elif not bool(items):
    print("items is Empty")
```  

bool()을 사용하는 방법은 숫자형 데이터도 사용 가능합니다  
  
단, None 여부를 판단할 때는 아래 방법을 사용합니다  

```
if item is None:
    print("item is None")
```  
