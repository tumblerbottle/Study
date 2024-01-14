# 회귀: 평균으로의 회귀
# 회귀분석을 위해...1)산점도 확인 2)최적의 직선 확인 3)분산분석 4)t/z검정
# 1. 단순선형회귀분석: 예측.결과변수 1개, 차수 1차/ 오차의 정규성, 독립성, 등분산성 가정
# 2. 다중선형회귀분석석: 여러 독립변수와 하나의 종속 변수의 선형관계
#                       가정 -> 각 독렵변수는 종속변수와 선형관계 존재,
#                               독립변수 간 높은 상관관계 x, 잔차가 정규분포를 이룸
# 3. 위계적 회귀분석: 연구자가 직접 '영향력'이 큰 변수를 투입하며 확인인


# Q1 longley 데이터 셋을 사용하여, 다중 회귀분석 수행
str(longley)
View(longley)

# 상관관계 분석
summary(longley)
corre<-cor(longley)
print(corre)

# 다중회귀분석
library(MASS)
d_reg<-lm(GNP~GNP.deflator+Unemployed+Population+Armed.Forces+Year+Employed,data=longley)
summary(d_reg)  # unemployed, population과 **수준의 상관관계

d2_reg <- lm(GNP~Year+Population+GNP.deflator+Unemployed,data=longley)
summary(d2_reg) # population, unemployed와 ***수준의 상관관계



# Q2 위계적 회귀분석으로 employed에 대해 기장 영향력이 큰 변수 확인 및 분석의 다중공선성 확인
# 위계적 회귀분석
# 변수를 추가하거나 삭제하는 방향으로 진행행
h_reg<-lm(Employed~GNP.deflator+GNP+Population+Armed.Forces+Year+Unemployed,data=longley)
summary(h_reg)

## gnp.deflator이랑 population 삭제, p=0.8885
h2_reg <- lm(Employed~GNP+Armed.Forces+Year+Unemployed,data=longley)
summary(h2_reg)
anova(h_reg,h2_reg)

# Unemployed 삭제, p=0.002535 **
h3_reg<- lm(Employed~GNP.deflator+GNP+Population+Armed.Forces+Year,data=longley)
anova(h_reg,h3_reg)

# year 삭제, p=0.003037 **
h4_reg<-lm(Employed~GNP.deflator+GNP+Population+Armed.Forces+Unemployed,data=longley)
anova(h_reg, h4_reg)

# armed.forces 삭제,p=0.0009444 *** 가장 영향력이 큼
h5_reg<-lm(Employed~GNP.deflator+GNP+Population+Year+Unemployed,data=longley)
anova(h_reg, h5_reg)

# 다중공선성 확인
library(car)
vif(h_reg)  # 여기서 다중공선성이 작을수록 큰 영향력을 가짐
tolerance<-1/vif(h_reg) # 다중공선성의 역수, 클수록 큰 영향력
summary(tolerance)
### armed.forces가 가장 유의미한 예측 변수임.
