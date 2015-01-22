function svd(file_name, r)
document_term_matrix=0;
A = csvread(file_name, 1, 1);
[U, S, V] = svd(A, 'econ'); % Performing SVD
for i = 1:r[sortedX,sortingIndices] = sort(U(:,i),'descend'); % Ranking each latent semantic
for j= 1:size(U(:,i),1)
simulation_file(j,1) = sortingIndices(j);
simulation_score(j,1) = U(sortingIndices(j), i);
end
disp([simulation_file simulation_score]); % Display the latent semantic
end
csvwrite('indices.csv',sortingIndices(1:r));
csvwrite('3a_U_Matrix.csv',U(:,1:r));
csvwrite('3a_V_Matrix.csv',V(:,1:r));
csvwrite('3a_S_Matrix.csv',S(1:r,1:r));
end