
def solution(skill, skill_trees):
    answer = len(skill_trees)
    for skill_tree in skill_trees:
        index = 0
        for s in skill_tree:
            if s in skill:
                if s == skill[index]:
                    index += 1
                else:
                    answer -= 1
                    break
    return answer

  