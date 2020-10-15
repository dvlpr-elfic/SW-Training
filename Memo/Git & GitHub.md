
# Git & GitHub

지옥에서 온 문서관리자 깃&깃허브 입문 책을 비롯해 실제 사용하면서 정리하는 Tip 입니다

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

p.69

## conflict

p.113