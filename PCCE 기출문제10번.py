def solution(data, ext, val_ext, sort_by):
    answer = []
    data_dict={"code":0,"date":1,"maximum":2,"remain":3}
    val_ext_list=[]
    for x in range(len(data)):
        if (data[x][data_dict[ext]]<val_ext):
            answer.append(data[x])
    print(answer)
    answer=sorted(answer, key=lambda x : x[data_dict[sort_by]])
    return answer