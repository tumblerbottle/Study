# 범주형 자료는 범주로 나뉜 자료로, 순서 없으면 명목형, 있으면 순서형
# 범주형-연속형  -> t-검정, 분산분석(anova)로 분석
# 범주형-범주형 -> 분할표 분석, 카이제곱 검정, 피셔의 정확도 검정으로 분석
# 연속형-범주형 -> 로지스틱 회귀 분석으로 분석

# 빈도분석: 분포 특성 파악. mean, median, mode, sd 등 확인 가능
# 적합도 검정 : 모집단이 일정한 확률분포를 가짐을 '가정'할 때 표본 자료가 
#               모집단 분포가정에 적합한지 검검정 ex. 단일 표본 카이제곱 검정 등
#               H0 표본이 모집단의 분포 따름 // H1 따르지 않음음
# 교차 분석 : 두 범주형 변수 간의 연관성 검정. 샘플 수가매우 적거나 카테고리가
#               많은 경우 사용. 
# 차이검정-t-검정 : 두 집단 간 평균을 비교 (대응표본t-test는 한 집단 기준)
#               30개 이하의 표본에 사용, 귀무가설 확인용, 
#               모집단의 분석/표준편차차 모를 때 사용
#               1. 단일표본 : H0 모집단 평균==표본 평균  // H1 다름
#               2. 독립표본 : H0 두 집단 평균 동일 // H1 다름
#               3. 대응표본 : H0 사전 사후 평균 동일 // H1 다름
# 차이검정-분산분석 : 두 개 이상 집단의 평균 분석, f-분포 사용. 
#               정규성(변인은 정규분포),등분산성(변인의 모분산은 동일),독립성가정
#               1. 일원분산분석: 요인이 1개, 수준이 3개, H0 모든 집단 평균 동일
#               2. 이원분산분석: 요인이 2개, H0 상호작용 효과가 없다
#               3. 다변량분산분석: 종속변인 2개이상, H0 모든 집단의 평균벡터 동일
#               4. 공분산분석: 로지스틱회귀(하나의 종속변수와 여러 독립 변수 간의
#                               다변수 회귀관계 조사 가능)
#로지스틱 회귀분석: S자 형태의 선을 그어 회귀관관계 확인
#그 외: 순서형/다항/조건부 로지스틱 회귀분석, 포아송 회귀분석 존재



#Q1 ChickWeight 데이터로 분산분석과 사후검정 하기

library(lme4)
data(ChickWeight)
# str 함수는 데이터 프레임 미리보기 제공
str(ChickWeight)

# 분산분석
# 상호작용의 경우, * 사용
cw.aov <- aov(weight~Time+Diet,data=ChickWeight)
summary(cw.aov)
result1<-aov(weight~Time, data=ChickWeight) # 통계적 유의미
result2<-aov(weight~Diet, data=ChickWeight) # 통계적 유의미
result3<-aov(weight~Diet*Time, data=ChickWeight) # 상호작용 존재
anova(result3)

# 사후검정
# install.packages("multcomp")  
library(multcomp)
ChickWeight$Time <- as.factor(ChickWeight$Time)
cw2.aov <- aov(weight~Time+Diet+Time*Diet, data=ChickWeight)
tuk.hsd<-TukeyHSD(cw2.aov,conf.lev= 0.95)

plot(tuk.hsd,las=1,col="orange")


# Q2 mtcars 데이터로 로지스틱회귀분석, 모델 적합성은 검정 카이제곱 검정 수행

# 로지스틱 회귀분석
library(dplyr)
mtcars
big<-mtcars %>% filter(mpg>median(mpg))
small<-mtcars %>% filter(mpg<=median(mpg))
big <- mutate(big,median=1)  # 열 추가
small <- mutate(small,median=0)

log_model <- glm(median ~ mpg, data = rbind(big, small), family = "binomial")
summary(log_model)

# 카이제곱 검정
# install.packages("lmtest")
library(lmtest)
null_model <- glm(median ~ 1, data = rbind(big, small), family = "binomial")
lr_test <- lrtest(null_model, log_model) # 통계적 유의미미
print(lr_test)
