int Altura(struct TreeNode *root){
	int iEsq = 0;
	int iDir = 0;

	if (root == NULL){
		return 0;
	}

	iEsq = Altura(root->left);
	iDir = Altura(root->right);

	if (iEsq > iDir){
		return iEsq+1;
	}else{
		return iDir+1;
	}
}
int maiorValor(struct TreeNode *root){
	int maior;
		if (root->left != NULL && root->right != NULL){
			if (root->left->val > root->right->val){
				maior = maior = root->left->val;
			}else{
				maior = root->right->val;
			}
		}else if (root->left == NULL && root->right != NULL){
			maior = root->right->val;
		}else if (root->left != NULL && root->right == NULL){
			maior = root->left->val;
		}
	return maior;
}

int maiorLinha(struct TreeNode *root, int linha){
    int valor1 = 0;
    int valor2 = 0;
    if (root == NULL){
    return 0;
    }

    valor1 = maiorLinha(root->left, linha-1);
    valor2 = maiorLinha(root->right, linha-1);
    if (valor1 != 0 || valor2 != 0){
        return valor1 > valor2 ? valor1 : valor2;
    }
    if (linha != 0 ){
        return 0;
    }else{
        valor1 = root->val;
        return valor1;
    }
     

}

int *largestValues( struct TreeNode *root, int *returnSize ) {
/* >>> ESCREVA SUA SOLUÇÃO AQUI DENTRO <<< */
	int *res;
	int linha = 0;
	if (root == NULL){
		return NULL;
	}else {
        *returnSize = Altura(root);
		res = malloc (sizeof(int) * (*returnSize));
		res[0] = root->val;
        linha++;
	}
    while (linha < *returnSize){
        res[linha] = maiorLinha(root, linha);
        linha++;
    }
	return res;
}

