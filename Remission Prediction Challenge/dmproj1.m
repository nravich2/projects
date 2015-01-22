function DMPROJ1()
filename='input.csv';
count=0;
newData1=0;
A= xlsread(filename);
V_Matrix=xlsread('3a_V_Matrix.csv');
S_Matrix=xlsread('3a_S_Matrix.csv');
features = A(:,(1:110));
classLabels=A(:,111);
nTrees=49;
B=TreeBagger(nTrees,features,classLabels,'Method','classification');
C=xlsread('indices.csv');
D=xlsread('Baseline2_Testing.csv');
[r,c]=size(C);
[a,b]=size(D);
for i=1:a
for j=1:r
newData1(j)=D(i,C(j));
end
newData2=D(i,:);
Query_cordinates = newData2*V_Matrix* inv(S_Matrix);
predChar1=B.predict(Query_cordinates);
predictedClass(i)=str2double(predChar1);
end
disp(predictedClass);
load input.csv
indices=crossvalind('Kfold',600,10);
cp=classperf(classLabels);
for i = 1:5
test = (indices == i);
train = ~test;
class =classify(features(test,:),features(train,:),classLabels(train,:),'diaglinear');
classperf(cp,class,test);
end
max(cp.CorrectRate)
end