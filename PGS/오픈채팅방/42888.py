# [PGS] 오픈채팅방 / lv2 / 20분쯤?
# 문자열 처리는 그냥 파이썬으로 하자... 이참에 코테 언어를 파이썬으로 해야하나
# 그냥 단순 구현문제 C++로 했으면 map 썻을 듯

def solution(record):
    answer = []
    user={}
    for i in record:
        now=i.split()
        if now[0]=="Enter":
            user[now[1]]=now[2]
            answer.append(now[1]+"님이 들어왔습니다.")
        if now[0]=="Leave":
            answer.append(now[1]+"님이 나갔습니다.")
        if now[0]=="Change":
            user[now[1]]=now[2]
            
    # uid 닉네임으로 변경
    ret=[]
    for i in answer:
        name=user[i.split("님이")[0]]
        ret.append(i.replace(i.split("님이")[0],name))
        
    return ret