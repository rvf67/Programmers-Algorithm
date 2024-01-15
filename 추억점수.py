def solution(name, yearning, photo):
    answer = [0 for x in photo]
    name_dict={}
    answer_num=0
    for x in range(len(name)):
        name_dict[name[x]]=yearning[x]
    for photos in photo:
        
        for y in range(len(photos)):
            if photos[y] in name_dict:
                answer[answer_num]+=name_dict[photos[y]]
        answer_num+=1
    print(answer)
    return answer
solution(["may", "kein", "kain", "radi"],[5, 10, 1, 3],[["may", "kein", "kain", "radi"],["may", "kein", "brin", "deny"], ["kon", "kain", "may", "coni"]])
