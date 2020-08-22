# SW-Training  

언어, 자료구조, 알고리즘, WEB, 네트워크 등 SW 기초를 트레이닝 합니다  

## Problem Solving Site  
<a href='https://boj.kr'>Baekjoon Online Judge</a><br>
<a href='https://www.swexpertacademy.com'>Samsung SWEA</a><br>
<a href='https://algospot.com'>ALGOSPOT</a><br>
<a href='https://leetcode.com/'>LeetCode</a><br>
<a href='https://programmers.co.kr/'>Programmers</a><br>

## Problem List  

[code.plus](https://code.plus) 강의에 제시되는 문제들 중 일부입니다  

### 수학  

- [나머지](http://boj.kr/10430)
- [최대공약수와 최소공배수](http://boj.kr/10430)
- [최소공배수](http://boj.kr/2609)
- [GCD 합](http://boj.kr/9613)
- [소수 찾기](http://boj.kr/1978)
- [골드바흐의 추측](http://boj.kr/6588)

### 브루트포스  

- [일곱 난쟁이](http://boj.kr/2309)
- [날짜 계산](http://boj.kr/1476)
- [테트로미노](http://boj.kr/14500)
- [1,2,3 더하기](http://boj.kr/9095)
- [다음 순열](http://boj.kr/10972)
- [이전 순열](http://boj.kr/10973)
- [모든 순열](http://boj.kr/10974)
- [차이를 최대로](http://boj.kr/10819)
- [외판원 순회 2](http://boj.kr/10971)
- [로또](http://boj.kr/6603)
- [연산자 끼워넣기](http://boj.kr/14888)
- [암호 만들기](http://boj.kr/1759)
- [부분수열의 합](http://boj.kr/1182)
- [퇴사](http://boj.kr/14501)
- [연산자 끼워넣기(2)](http://boj.kr/15658)
- [집합](http://boj.kr/11723)

### 브루트포스 (N과 M연습)  

- [N과M(1)](http://boj.kr/15649)
- [N과M(2)](http://boj.kr/15650)
- [N과M(3)](http://boj.kr/15651)
- [N과M(4)](http://boj.kr/15652)
- [N과M(5)](http://boj.kr/15654)
- [N과M(6)](http://boj.kr/15655)
- [N과M(7)](http://boj.kr/15656)
- [N과M(8)](http://boj.kr/15657)
- [N과M(9)](http://boj.kr/15663)
- [N과M(10)](http://boj.kr/15664)
- [N과M(11)](http://boj.kr/15665)
- [N과M(12)](http://boj.kr/15666)


### 그래프와 BFS  

- [ABCDE](http://boj.kr/13023)
- [DFS와 BFS](http://boj.kr/1260)
- [연결 요소](http://boj.kr/11724)
- [이분 그래프](http://boj.kr/1707)
- [단지번호붙이기](http://boj.kr/2667)
- [섬의 개수](http://boj.kr/4963)
- [미로 탐색](http://boj.kr/2178)
- [토마토](http://boj.kr/7576)
- [숨바꼭질](http://boj.kr/1697)
- [이모티콘](http://boj.kr/14226)
- [숨바꼭질 3](http://boj.kr/13549)
- [알고스팟](http://boj.kr/1261)
- [벽 부수고 이동하기](http://boj.kr/2206)
- [탈출](http://boj.kr/3055)

### 다이나믹 프로그래밍  

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

