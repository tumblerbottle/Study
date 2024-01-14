# 주성분 분석
# 내장 함수 prcomp 사용
str(USArrests)
USArrests

pca_result<-prcomp(USArrests,scale=TRUE)
summary(pca_result)
# Cumulative Proportion을 확인하고, 몇번째 주성분까지만 사용할 것인지 선정
# 3번째 주성분까지만 사용해도 약 95% 설명 가능함

# screeplot으로 시각화하기
plot(pca_result,type='l')
# 꺾임이 큰 부분이 설명력이 큰 성분임을 의미함.

# fviz_contrib으로 주성분에 대한 기존 변수의 기여도 시각화하기
install.packages('devtools')
library(factoextra)
dim_1st <-fviz_contrib(pca_result, "var",axes = 1)
dim_2nd <-fviz_contrib(pca_result, "var",axes = 2)
dim_3rd <-fviz_contrib(pca_result, "var",axes = 3)
dim_4th <-fviz_contrib(pca_result, "var",axes = 4)
dim_1st # 3가지 요인을 잘 설명함
dim_2nd # 1가지 요인만 잘 설명함
dim_3rd # 1가지 요인만 잘 설명함
dim_4th # 2가지 요인을 잘 설명함
# 요인분석과 달리 주성분 분석은 첫번째 성분이 가장 많은 것을 설명하며 가장 중요함.

# 주성분 간에는 상관관계가 없음
cor(pca_result$x)

# 성분 적재값 확인하기
round(pca_result$rotation,3)
# 절댓값으로의 크기가 클 수록 성분과 변수 간 관련성이 높음을 의미함.

# 성분점수 확인하기
round(scale(USArrests) %*% pca_result$rotation, 3)
## prcomp함수는 각 케이스에 대한 성분점수를 계산 후 주성분의 x원소에 행렬형태로 저장하기에...
round(pca_result$x,3)
# 이렇게 표현해도 동일하게 나옴.

biplot(pca_result,cex=c(0.5,0.75))
# fviz_contrib 함수를 통해 주성분1은 assult,rape,murder을, 주성분 2는 urbanpop을 잘 설명함을 확인함.
# biplot에서 축과 평행일수록 밀접한 상관을 가짐을 의미함.
# 따라서, pc1은 assult, murder, rape 과 상관을, pc2는 urbanpop과 상관을 가짐을 확인할 수 있음. 


