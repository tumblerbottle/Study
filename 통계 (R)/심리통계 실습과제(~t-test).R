# Q1 R STUDIO

library("readr")
Q1 <- read.csv("Q1.csv")
X1 <- Q1$X1
mean(X1)
var(X1)
sqrt(var(X1))
sd(X1)
range(X1)
IQR(X1)
summary(X1)

# box plot
library(ggplot2)
ggplot(data=Q1)+
  geom_boxplot(mapping = aes(x=X1))+
  coord_flip()+labs(title="X1 BOXPLOT",x="X1")

# histogram
library(ggplot2)
ggplot(data=Q1)+
  geom_histogram(mapping = aes(x=X1),binwidth=2)+
  labs(title="Histogram", x="X1", y="Frequency")


# Q2 R STUDIO  
library("readr")
Q2 <- read.csv("Q2.csv")
View(Q2)
Gender <- Q2$Gender
Height <- Q2$Height
Weight <- Q2$Weight

# scatterplot for entire data
library(ggplot2)
ggplot(data=Q2)+
  geom_point(mapping=aes(x=Height, y=Weight))+
  labs(title="Scatterplot", x="Height", y="Weight")

# pearson cor. entire
cor(Height,Weight,method="pearson")

# male & female data
library(dplyr)
Q2.n <- mutate(Q2,
       Gender.n=factor(Gender,
                       levels = c(1,2),
                       labels = c("Male","Female"),
                       order=TRUE))
library(aplpack)
Gender.f <- filter(Q2.n,Gender.n == "Female")
Gender.m <- filter(Q2.n,Gender.n == "Male")

#female scatterplot
ggplot(data=Gender.f)+
  geom_point(mapping=aes(x=Height, y=Weight))+
  labs(title="Scatterplot", x="Height", y="Weight")

# female pearson cor.
Height.f <- Gender.f$Height
Weight.f <- Gender.f$Weight
cor(Height.f, Weight.f, method="pearson")

# male scatterplot
ggplot(data=Gender.m)+
  geom_point(mapping=aes(x=Height, y=Weight))+
  labs(title="Scatterplot", x="Height", y="Weight")

# male pearson cor.
Height.m <- Gender.m$Height
Weight.m <- Gender.m$Weight
cor(Height.m, Weight.m,method="pearson")


#Q3 R STUDIO
vh <- read.csv("VH.csv")
summary(vh$length)
library(dplyr)
vh <- mutate(vh,
               Class=factor(vh$Class,
                               levels = c(1,2),
                               labels = c("class1","class2"),
                               order=TRUE))
# <two independent samples t-test>
  length <- vh$length
  class <- vh$Class
# sample mean
  xbars <- tapply(length,class,mean)
  x1bar <- xbars[1]
  x2bar <- xbars[2]
  x2bar
# variance
  vars <- tapply(length,class,var)
  var2 <- vars[2]
  var1 <- vars[1]
  
# sample size
  n1 <- 54
  n2 <- 58
# degree of freedom
  df1 <- 53
  df2 <- 57
# pooled sample variance
  var.p <- (df1*var1 + df2*var2)/(df1+df2)
# standard error of the mean difference
  se.d <- sqrt(var.p*(1/n1 + 1/n2))
# t.stat from the mean difference
  t.d <- (x1bar-x2bar)/se.d
# critical value, two-tailed test, a=0.05
  tcv <- qt(p=0.975,df=110, lower.tail = TRUE)
#p-value
  pt(q=t.d,df=110,lower.tail=FALSE)
# because t.difference is included in critical value -> null hypothesis is true 

class1 <- filter(vh, class=="class1")
class2 <- filter(vh, class=="class2")
var(class1$length)
var(class2$length)
  
# 95% confidence interval
  tcv.025 <- qt(p=0.025, df=110, lower.tail=TRUE)
  tcv.975 <- qt(p=0.975, df=110, lower.tail=TRUE)
  (x1bar-x2bar)+tcv.025*se.d
  (x1bar-x2bar)+tcv.975*se.d
# because confidence interval does include 0 -> null hypothesis is true
