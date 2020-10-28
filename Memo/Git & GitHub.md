
# Git & GitHub

지옥에서 온 문서관리자 깃&깃허브 입문

## git checkout

HEAD가 가리키는 branch를 바꿉니다 (branch를 선택합니다)

```bash
git checkout $branch_name
```

현재까지의 변경사항 되돌리기

```bash
git checkout -- $file_name
```

이 두 가지 기능은 각각 `git switch` 와 `git restore`로도 사용가능하다

## git log

여태까지의 커밋 히스토리를 보여줍니다

```bash
> git log
commit &hash_code (HEAD -> master, origin/master, origin/HEAD)
Author: &user_name <account@email.com>
Date:   Tue Oct 13 23:41:53 2020 +0900

    $commit_message
```

## git diff

현재 작업 트리에서 diff를 출력합니다

```bash
> git diff
diff --git a/Memo/Git & GitHub.md b/Memo/Git & GitHub.md
index e69de29..be4c510 100644
--- a/Memo/Git & GitHub.md
+++ b/Memo/Git & GitHub.md
@@ -0,0 +1,42 @@
# changes ...
```

## git stash

아직 마무리하지 않은 작업을 stack에 잠시 저장합니다
commit 하기 전에 저장해두었다가 나중에 다시 pop 해서 반영할 수 있습니다

저장하기
```bash
> git stash save
```

stash 목록
```bash
> git stash list
```

pop해서 적용하기
```bash
> git stash pop
> git stash apply; git stash drop;	# 위 명령어와 같습니다
```

## git reset

수정된 파일을 스테이징(git add) 했을 때, 되돌리는 기능입니다

HEAD가 가리키는 브랜치의 최신 커밋 되돌리기
```bash
> git reset HEAD^
```

HEAD가 가리키는 브랜치에서 스테이징 되어있는 파일 되돌리기
```bash
> git reset HEAD $file_name
```

## conflict

두 브랜치를 merge할 때 같은 file의 같은 line에 서로 다른 수정사항이 있으면 conflic가 발생합니다

그 때 충돌된 파일을 열어보면 다음과 같이 표시되어 있습니다

```bash
<<<<<<< HEAD
$현재_브랜치의_수정사항
=======
$병합할_브랜치의_수정사항
>>>>>>> $branch
```
이때 `<<<<<<<`, `>>>>>>>`과 `=======`이 표시된 부분을 지우고 원하는 수정사항만 남기고 저장합니다

이후 파일을 스테이징하고 커밋하면 conflict가 발생하지 않습니다
