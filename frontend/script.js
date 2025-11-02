        // Store all transactions
        var transactions = [];
        var currentType = 'income';

        // Function to get categories based on type using switch case
        function getCategories(type) {
            switch(type) {
                case 'expense':
                    return ['Food', 'Transport', 'Shopping', 'Bills', 'Entertainment', 'Health', 'Other'];
                case 'income':
                    return ['Salary', 'Business', 'Investment', 'Gift', 'Other'];
                default:
                    return [];
            }
        }

        // Set transaction type (income or expense)
        function setType(type) {
            currentType = type;
            
            // Update button styling
            var expenseBtn = document.getElementById('expenseBtn');
            var incomeBtn = document.getElementById('incomeBtn');
            
            switch(type) {
                case 'expense':
                    expenseBtn.classList.add('active');
                    incomeBtn.classList.remove('active');
                    break;
                case 'income':
                    incomeBtn.classList.add('active');
                    expenseBtn.classList.remove('active');
                    break;
            }
            
            updateCategoryOptions();
        }

        // Update category dropdown based on selected type
        function updateCategoryOptions() {
            var categorySelect = document.getElementById('category');
            categorySelect.innerHTML = '<option value="">Select category</option>';
            
            var categoriesList = getCategories(currentType);
            
            // Add each category as an option
            for (var i = 0; i < categoriesList.length; i++) {
                var option = document.createElement('option');
                option.value = categoriesList[i];
                option.textContent = categoriesList[i];
                categorySelect.appendChild(option);
            }
        }

        // Add new transaction
        function addTransaction() {
            var description = document.getElementById('description').value.trim();
            var amount = parseFloat(document.getElementById('amount').value);
            var category = document.getElementById('category').value;

            // Check if all fields are filled
            if (!description || !amount || !category) {
                alert('Please fill all fields');
                return;
            }

            // Create new transaction object
            var transaction = {
                id: Date.now(),
                description: description,
                amount: amount,
                type: currentType,
                category: category,
                date: new Date()
            };

            // Add to beginning of array
            transactions.unshift(transaction);
            
            // Clear input fields
            document.getElementById('description').value = '';
            document.getElementById('amount').value = '';
            document.getElementById('category').value = '';

            // Update the display
            updateUI();
        }

        // Delete a transaction by id
        function deleteTransaction(id) {
            var newTransactions = [];
            
            // Keep all transactions except the one with matching id
            for (var i = 0; i < transactions.length; i++) {
                if (transactions[i].id !== id) {
                    newTransactions.push(transactions[i]);
                }
            }
            
            transactions = newTransactions;
            updateUI();
        }

        // Format amount as currency
        function formatCurrency(amount) {
            return 'Rs ' + Math.round(amount).toLocaleString('en-PK');
        }

        // Format date as short text
        function formatDate(date) {
            var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
            var month = months[date.getMonth()];
            var day = date.getDate();
            return month + ' ' + day;
        }

        // Calculate totals and update display
        function updateUI() {
            var totalIncome = 0;
            var totalExpense = 0;
            
            // Calculate totals using switch case
            for (var i = 0; i < transactions.length; i++) {
                switch(transactions[i].type) {
                    case 'income':
                        totalIncome = totalIncome + transactions[i].amount;
                        break;
                    case 'expense':
                        totalExpense = totalExpense + transactions[i].amount;
                        break;
                }
            }

            var balance = totalIncome - totalExpense;

            // Update stat cards
            document.getElementById('totalIncome').textContent = formatCurrency(totalIncome);
            document.getElementById('totalExpense').textContent = formatCurrency(totalExpense);
            document.getElementById('balance').textContent = formatCurrency(balance);

            var transactionList = document.getElementById('transactionList');
            
            // Show empty message if no transactions
            if (transactions.length === 0) {
                transactionList.innerHTML = '<div class="empty-state"><p>No transactions yet. Add your first transaction!</p></div>';
                return;
            }

            // Build HTML for all transactions
            var html = '';
            for (var i = 0; i < transactions.length; i++) {
                var t = transactions[i];
                var sign = '';
                
                switch(t.type) {
                    case 'income':
                        sign = '+';
                        break;
                    case 'expense':
                        sign = '-';
                        break;
                }
                
                html = html + '<div class="transaction-item">' +
                    '<div class="transaction-info">' +
                        '<div class="transaction-desc">' + t.description + '</div>' +
                        '<div class="transaction-meta">' +
                            '<span class="transaction-category">' + t.category + '</span>' +
                            '<span>' + formatDate(t.date) + '</span>' +
                        '</div>' +
                    '</div>' +
                    '<div class="transaction-amount ' + t.type + '">' + sign + formatCurrency(t.amount) + '</div>' +
                    '<button class="delete-btn" onclick="deleteTransaction(' + t.id + ')">' +
                        '<svg viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">' +
                            '<path d="M3 6H21M8 6V4C8 3.44772 8.44772 3 9 3H15C15.5523 3 16 3.44772 16 4V6M19 6V20C19 20.5523 18.5523 21 18 21H6C5.44772 21 5 20.5523 5 20V6H19Z"/>' +
                        '</svg>' +
                    '</button>' +
                '</div>';
            }
            
            transactionList.innerHTML = html;
        }

        // Initialize on page load
        updateCategoryOptions();
        updateUI();