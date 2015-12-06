close all
clear all
cgParallel = importdata('out_CG_parallel2.txt',' ',1);
timeseq = 0.28370690;

%%
figure;
hold on
plot([0 cgParallel.data(1:7,2)'],[timeseq cgParallel.data(1:7,3)'],'x-');
plot([0 cgParallel.data(8:14,2)'],[timeseq cgParallel.data(8:14,3)'],'x-');
plot([0 cgParallel.data(15:21,2)'],[timeseq cgParallel.data(15:21,3)'],'x-');
%plot([0 cgParallel.data(22:28,2)'],[timeseq cgParallel.data(22:28,3)'],'x-');
xlabel('Number of threads');
ylabel('Running time');
title('Runningtime for nodes running with varying number of threads');
legend('1 node','2 nodes', '4 nodes')
set(gca,'xscale','log')
grid on
hold off


%%
figure;
hold on
plot([0 cgParallel.data(1:7,2)'],timeseq./[timeseq cgParallel.data(1:7,3)'],'x-');
plot([0 cgParallel.data(8:14,2)'],timeseq./[timeseq cgParallel.data(8:14,3)'],'x-');
plot([0 cgParallel.data(15:21,2)'],timeseq./[timeseq cgParallel.data(15:21,3)'],'x-');
%plot([0 cgParallel.data(22:28,2)'],timeseq./[timeseq cgParallel.data(22:28,3)'],'x-');
xlabel('Number of threads');
ylabel('Speedup');
set(gca,'xscale','log') 
legend('1 node','2 nodes', '4 nodes');
title('Speedup for nodes running with varying number of threads');
grid on
hold off
