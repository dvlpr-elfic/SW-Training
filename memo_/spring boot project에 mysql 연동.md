# Spring Boot Project에 MySQL 연동

spring boot project에 jpa와 mysql을 연동하는 방법입니다



## Install MySQL

아래 링크의 게시물을 참조해서 설치했습니다

[참조 링크](https://dog-developers.tistory.com/20)



## CREATE DATABASE

"MySQL Command Line Client"을 실행합니다



설치할 때 세팅했던 비밀번호를 입력합니다
```bash
Enter password: ****
Welcome to the MySQL monitor.
```



현재 사용 가능한 database를 확인합니다

```bash
mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sakila             |
| sys                |
| world              |
+--------------------+
6 rows in set (0.01 sec)
```



이름이 겹치지 않도록 데이터베이스를 생성합니다

```bash
mysql> create database db_test
Query OK, 1 row affected (0.01 sec)
```



## Setting build.gradle

build.gradle 파일에 의존성을 추가합니다

```groovy
dependencies {
	implementation 'org.springframework.boot:spring-boot-starter-data-jpa'
	compile 'mysql:mysql-connector-java'
}
```



만약 다른 데이터베이스의 의존성이 있다면 주석처리하거나 삭제합니다

```groovy
dependencies {
//	runtimeOnly 'com.h2database:h2'
}
```



## Setting application.properties

```bash
server.address=localhost
server.port=8080

# API 호출시, SQL 문을 콘솔에 출력한다.
spring.jpa.show-sql=true

# DDL 정의시 데이터베이스의 고유 기능을 사용합니다.
# ex) 테이블 생성, 삭제 등
spring.jpa.generate-ddl=true

# DB 초기화 전략을 설정합니다
spring.jpa.hibernate.ddl-auto = update

# MySQL 을 사용할 것.
spring.jpa.database=mysql

# MySQL 설정
spring.datasource.url=jdbc:mysql://localhost:3306/db_test?useSSL=false&characterEncoding=UTF-8&serverTimezone=UTC
spring.datasource.username=root
spring.datasource.password=$password
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver

# MySQL 상세 지정
spring.jpa.database-platform=org.hibernate.dialect.MySQL5InnoDBDialect
```

아래 설정의 `db_test` 부분을 create database $database_name 으로 생성했던 데이터베이스 이름으로 세팅해줍니다

spring.datasource.url=jdbc:mysql://localhost:3306/db_test?useSSL=false&characterEncoding=UTF-8&serverTimezone=UTC



## Test

아래와 같이 Entity, Repository를 구현하고 unit test를 통해 검증합니다



MyEntity.java

```java
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Data
public class MyEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String content;

    public MyEntity(String content) {
        this.content = content;
    }
}
```



MyEntityRepository.java

```java
public interface MyEntityRepository extends JpaRepository<MyEntity, Long> {
    List<MyEntity> findByContent(String content);
}
```



MyEntityRepositoryTest.java

```java
@SpringBootTest
class MyEntityRepositoryTest {
    @Autowired
    private MyEntityRepository myEntityRepository;

    @BeforeEach
    void before() {
        myEntityRepository.save(new MyEntity("test1"));
        myEntityRepository.save(new MyEntity("test2"));
    }

    @Test
    void crud() {
        List<MyEntity> result = myEntityRepository.findAll();

        assertThat(result.size()).isEqualTo(2);
        assertThat(result.get(0).getContent()).isEqualTo("test1");
    }
}
```

