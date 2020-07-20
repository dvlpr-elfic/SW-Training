# SW-Training  

자료구조, 알고리즘, WEB, 네트워크 등 SW 기초를 트레이닝 합니다  

## Problem Solving Site  
<a href='https://boj.kr'>Baekjoon Online Judge</a><br>
<a href='https://www.swexpertacademy.com'>Samsung SWEA</a><br>
<a href='https://algospot.com'>ALGOSPOT</a><br>
<a href='https://leetcode.com/'>LeetCode</a><br>
<a href='https://programmers.co.kr/'>Programmers</a><br>

## Python  

### 자료구조의 Empty 판단  

str, list, set, tuple, dict 등 자료구조의 Empty 판단은 bool() 메소드를 사용하거나 조건문에 해당 객체를 바로 써주면 됩니다  

``` python
if items:
    print("items is not Empty")
elif not items:
    print("items is Empty")
```  

``` python
if bool(items):
    print("items is not Empty")
elif not bool(items):
    print("items is Empty")
```  

bool()을 사용하는 방법은 숫자형 데이터도 사용 가능합니다  
  
단, None 여부를 판단할 때는 아래 방법을 사용합니다  

``` python
if item is None:
    print("item is None")
```  

## Java  

### HashMap Iterate  

java.util.HashMap의 모든 요소를 방문할 때는 Set을 사용하면 쉽게 할 수 있습니다  

``` java
for (String key : hashMap.keySet()) {
    System.out.println("key : " + key + ", value : " + hashMap.get(key));
}
```  

HashMap.keySet()을 이용하여 key의 집합(set)을 구하고 value는 다시 HashMap에서 찾는 방법으로 접근할 수 있습니다  

value 접근 방법에서 효율성 문제가 있을 수 있지만 key값의 길이가 길지 않다면 HashMap의 탐색 성능은 O(1)이므로 큰 문제는 없습니다  

``` java
for (Map.Entry<String, Integer> entry : hashMap.entrySet()) {
    System.out.println("key : " + entry.getKey() + ", value : " + entry.getValue());
}
```  

비슷한 방법이지만 key의 집합만 구하는 것이 아니라 key, value를 한 쌍으로 가지는 entry의 집합을 구해서 HashMap의 모든 요소를 방문하는 예제입니다  

본인이 가장 많이 쓰는 방법입니다  

## Tech-Interview  

https://github.com/JaeYeopHan/Interview_Question_for_Beginner

https://github.com/gyoogle/tech-interview-for-developer

