close all
clear all
cgParallel = importdata('out_CG_parallel.txt',' ',1);
timeseq = 0.16294694;

%%
figure;
hold on
plot([0 cgParallel.data(1:6,2)'],[timeseq cgParallel.data(1:6,3)'],'x-');
plot([0 cgParallel.data(7:12,2)'],[timeseq cgParallel.data(7:12,3)'],'x-');
plot([0 cgParallel.data(13:18,2)'],[timeseq cgParallel.data(13:18,3)'],'x-');
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
plot([0 cgParallel.data(1:6,2)'],timeseq./[timeseq cgParallel.data(1:6,3)'],'x-');
plot([0 cgParallel.data(7:12,2)'],timeseq./[timeseq cgParallel.data(7:12,3)'],'x-');
plot([0 cgParallel.data(13:18,2)'],timeseq./[timeseq cgParallel.data(13:18,3)'],'x-');
%plot([0 cgParallel.data(22:28,2)'],timeseq./[timeseq cgParallel.data(22:28,3)'],'x-');
xlabel('Number of threads');
ylabel('Speedup');
set(gca,'xscale','log') 
legend('1 node','2 nodes', '4 nodes');
title('Speedup for nodes running with varying number of threads');
grid on
hold off