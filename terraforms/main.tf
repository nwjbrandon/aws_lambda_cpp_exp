terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.46.0"
    }
  }
  required_version = "~> 1.3.6"
}

resource "aws_ecr_repository" "test_ecr_repository" {
  name = "test"

  image_scanning_configuration {
    scan_on_push = true
  }
}

resource "aws_iam_role" "lambda_iam_role" {
  name               = "lambda_iam_role"
  assume_role_policy = file("lambda_iam_role_policy.json")
}

resource "aws_iam_policy" "lambda_iam_policy" {
  name        = "lambda_iam_policy"
  description = "lambda_iam_policy"

  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = [
          "lambda:InvokeFunction",
        ]
        Effect   = "Allow"
        Resource = "*"
      },
    ]
  })
}

resource "aws_iam_role_policy_attachment" "lambda_iam_role_policy_attachment" {
  role       = aws_iam_role.lambda_iam_role.name
  policy_arn = aws_iam_policy.lambda_iam_policy.arn
}

resource "aws_iam_role_policy_attachment" "lambda_iam_role_policy_attachment_AWSLambdaBasicExecutionRole" {
  role       = aws_iam_role.lambda_iam_role.name
  policy_arn = "arn:aws:iam::aws:policy/service-role/AWSLambdaBasicExecutionRole"
}

resource "aws_lambda_function" "test" {
  function_name = "test"
  architectures = ["x86_64"]
  role          = aws_iam_role.lambda_iam_role.arn
  image_uri     = "131791614471.dkr.ecr.ap-southeast-1.amazonaws.com/test:test-v0"
  package_type  = "Image"
  memory_size   = 8192
  timeout       = 60
}